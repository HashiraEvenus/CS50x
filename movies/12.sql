SELECT title FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON movies.id = stars.movie_id
WHERE name = "Johnny Depp" 
AND title IN (SELECT title FROM movies 
JOIN people ON people.id = stars.person_id
JOIN stars ON movies.id = stars.movie_id
WHERE name = "Helena Bonham Carter" );