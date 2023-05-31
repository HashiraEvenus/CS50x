-- Keep a log of any SQL queries you execute as you solve the mystery.
-- See the scene report that took place on Humphrey Street on 7/28
SELECT description FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND year = 2021
AND street = "Humphrey Street";

-- See the name of people that were in during theft
SELECT name FROM people 
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs 
WHERE  day = 28 AND month = 7 AND hour = 10 AND minute BETWEEN 0 AND 16 AND year = 2021 );

--See the interviews from the day of the theft
SELECT * FROM interviews
WHERE day = 28 AND month = 7 AND year = 2021;

--Check parking lot from 10:15 to 10:25
SELECT id,name, license_plate FROM people 
WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs 
WHERE activity = "exit" 
AND day = 28 AND month = 7 AND hour = 10 AND minute BETWEEN 15 AND 25 AND year = 2021 ); 

--Check ATM transactions on Legget Street before ID 162 name EUGENE arrived at bakery .
SELECT id,name FROM people
JOIN bank_accounts ON people.id = person_id
WHERE account_number IN (SELECT account_number FROM atm_transactions 
WHERE day = 28 AND month = 7  AND year = 2021 AND atm_location= "Leggett Street");

--LUCA MAIN SUSPECT!
--Check Luca's calls!
SELECT * FROM phone_calls
WHERE caller = (SELECT phone_number FROM people WHERE name = "Bruce"
AND day = 28 AND month = 7 AND year = 2021 and duration <= 60);
--See the name of the accomplice - person who he spoke right after the robbery.
SELECT name FROM people 
WHERE phone_number = "(375) 555-8161";
--MAIN SUSPECT'S ACCOMPLICE IS KATHRYN!
--Check earliest flight out of fiftyville on 29th. Accomplice bought ticket.
SELECT * FROM flights
WHERE day = 29 AND month = 7 AND year = 2021 ORDER BY(hour);
-- Earliest flight has the ID of 36

--Check the name of the airport the plane went to
SELECT * FROM airports
WHERE id = 4;
-- Suspect went to NYC

-- See if he was on the ealiest flight

SELECT name FROM people 
WHERE passport_number IN (SELECT passport_number FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE id = 36 AND passport_number = (SELECT passport_number FROM flights 
WHERE day = 29 AND month = 7 AND year = 2021));

-- Luca was on that plane
--Luca matches our thief's profile with all the evidence we have stacked against him
























