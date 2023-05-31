--Give me all of the stars
SELECT name FROM people 
JOIN stars ON people.id = stars.person_id
JOIN movies ON movies.id = stars.movie_id
--From the movies that Kevin Bacon starred
WHERE movies.id IN (SELECT stars.movie_id FROM movies
JOIN people ON  people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
WHERE name = "Kevin Bacon") AND name != "Kevin Bacon";