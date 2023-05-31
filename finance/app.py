import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    db.execute("CREATE table IF NOT EXISTS stocks_owned(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER,symbol TEXT,name TEXT, price INTEGER, date DATETIME, shares INTEGER, cash_spent FLOAT, FOREIGN KEY (user_id) REFERENCES users(id))")
    symbols = db.execute("SELECT DISTINCT symbol FROM stocks_owned WHERE user_id=?", session["user_id"])
    cost = 0
    #updates prices in real time
    for symbol in symbols:
        print(symbol["symbol"])
        prices = lookup(symbol["symbol"])
        db.execute("UPDATE stocks_owned SET price=? WHERE symbol=? AND user_id=?", prices["price"], symbol["symbol"], session["user_id"])
        #Total cash formula
        shares = db.execute("SELECT (SUM(shares)*price) as totalcost FROM stocks_owned \
            WHERE symbol=? AND user_id=?",symbol["symbol"], session["user_id"])
        cost = cost + shares[0]["totalcost"]

    cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    stocks = db.execute("SELECT SUM(shares), symbol, name,price FROM stocks_owned WHERE user_id=? GROUP BY symbol", session["user_id"])
    return render_template("index.html", stocks=stocks, cash=cash[0]["cash"], cost=cost+cash[0]["cash"])

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    #Selects cash of user
    current_money = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"] )
    current_money = current_money[0]["cash"]
    if request.method=="POST":
        # Pass symbol and shares from buy.html form
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        #APOLOGY if shares weren't submitted
        if not shares:
            return apology("Missing shares", 400)
        #APOLOGY if shares are alphabetical
        elif shares.isalpha():
            return apology("Invalid shares",400)
        #APOLOGY if shares is decimal
        elif not shares.isdigit():
            return apology("Invalid shares",400)
        #APOLOGY if shares are 0 or less
        elif int(shares) < 1:
            return apology("Invalid shares",400)


        #Calls lookup to see the price of stock etc
        stock = lookup(symbol)
        # Create table for stocks owned by user
        db.execute("CREATE table IF NOT EXISTS stocks_owned(id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER,symbol TEXT,name TEXT, price INTEGER, date DATETIME, shares INTEGER, cash_spent FLOAT, FOREIGN KEY (user_id) REFERENCES users(id)) ")
        # Create table for symbols that have been bought
        if stock and shares:
            price = float(stock["price"])
            shares = int(shares)
            #APOLOGY Make current money - stocks final price for new balance'
            if price*shares > current_money:
                return apology("can't afford",400)
            #INSERT Stock to users database
            else:
                db.execute("INSERT INTO stocks_owned(symbol, shares, name, price, cash_spent, date, user_id) VALUES (?, ?, ?, ?, ?,CURRENT_TIMESTAMP, ?)",symbol,shares, stock["name"], price, price*shares, session["user_id"] )
                db.execute("UPDATE users SET cash = ? WHERE id = ?",(current_money-(price*shares)), session["user_id"])
                #TO DO: Bought successfuly message
                flash("Bought!")
                return redirect("/")
        #APOLOGY If stock doesn't exist return error
        elif not symbol:
            return apology("Missing symbol",400)
        #APOLOGY If symbol doesn't exist
        elif not stock:
            return apology("Invalid symbol", 400)


    return render_template("buy.html",money=current_money)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    table = db.execute("SELECT symbol, shares, price, date FROM stocks_owned WHERE user_id=?", session["user_id"])
    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method=="POST":
        sym = request.form.get("symbol")
        stock = lookup(sym)
        if stock:
            return render_template("quoted.html", stockname=stock["name"], stockprice=stock["price"], stocksymbol=stock["symbol"])
        else:
            return apology("Stock doesn't exist",400)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method=="POST":
    #Ensure username was provided
        if not request.form.get("username"):
            return apology("Must provide username",400)
    #Ensure password was provided
        if not request.form.get("password") or not request.form.get("confirmation"):
            return apology("Must provide password",400)
    #Ensure the passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords don't match",400)
    #Query database for username
        username = request.form.get("username")
        password = request.form.get("password")
        rows = db.execute("SELECT username FROM users WHERE username = ?", username)
        if len(rows) == 1:
            return apology("Username already exists")
        else:
            hash = generate_password_hash(password)
            db.execute("INSERT INTO users(username,hash) VALUES(?,?)",username,hash)

    return render_template("register.html")

@app.route("/cash", methods=["GET","POST"])
@login_required
def cash():
    """ADD CASH"""
    if request.method == "POST":
        money = request.form.get("money")
        db.execute("UPDATE users SET cash=cash+? WHERE id=?",money, session["user_id"])
        cash_owned = db.execute("SELECT cash FROM users WHERE id=?",session["user_id"])
        cash_owned = cash_owned[0]["cash"]
        if not money:
            return apology("Insert an amount",400)
        elif money.isalpha():
            return apology("INVALID SHARES",400)
        if int(money)<1:
            return apology("Insert valid amount",400)
        elif not money.isdigit():
            return apology("Invalid shares",400)
        flash("Cash Added!")
        return redirect("/")
    return render_template("cash.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_symbols = db.execute("SELECT DISTINCT symbol FROM stocks_owned WHERE user_id=?", session["user_id"])
    if request.method == "POST":

        shares = request.form.get("shares")
        stock = request.form.get("symbol")

        #APOLOGY User doesn't select a stock
        if stock is None:
            return apology("Missing symbol", 400)
        else:
            price=lookup(stock)
            allshares = db.execute("SELECT SUM(shares) as allshares FROM stocks_owned WHERE symbol=? AND user_id=? GROUP BY symbol",stock, session["user_id"])
            allshares = allshares[0]["allshares"]
            cash = db.execute("SELECT cash FROM users WHERE id=?",session["user_id"])
            cash = cash[0]["cash"]

        #APOLOGY Stock isn't owned
        for i in range(len(user_symbols)):
            if stock == user_symbols[i]["symbol"]:
                break
            elif i==len(user_symbols)-1 and (stock != user_symbols[i]["symbol"]):
                return apology("Symbol not owned", 400)
        #APOLOGY if shares weren't submitted
        if not shares:
            return apology("Missing shares", 400)
        #APOLOGY if shares are alphabetical
        elif shares.isalpha():
            return apology("Invalid shares", 400)
        #APOLOGY if shares is decimal
        elif not shares.isdigit():
            return apology("Invalid shares", 400)
        #APOLOGY if shares are 0 or less
        elif int(shares) < 1:
            return apology("Invalid shares", 400)
        #APOLOGY User sells more shares than he has
        elif int(shares) > int(allshares):
            return apology("Too Many shares", 400)
        #UPDATES SHARES
        newshares= allshares-int(shares)

        #UPDATES SHARES

        db.execute("INSERT INTO stocks_owned (symbol, shares, name, price, cash_spent, date, user_id) VALUES (?, ?, ?, ?, ?,CURRENT_TIMESTAMP, ?)"
        ,stock,-int(shares), price["name"], price["price"], int(price["price"]*int(shares)), session["user_id"] )
        sexo = db.execute("SELECT shares, symbol FROM stocks_owned WHERE user_id=?", session["user_id"])
        app.logger.info(sexo)
        #UPDATES CASH
        db.execute("UPDATE users SET cash=? where id=?", cash+int(price["price"]*int(shares)), session["user_id"] )
        #DELETES ROWS WHERE SHARES ARE 0
        #db.execute("DELETE FROM stocks_owned WHERE shares<=0")
        flash("Sold!")
        return redirect("/")

    return render_template("sell.html", symbols=user_symbols)


