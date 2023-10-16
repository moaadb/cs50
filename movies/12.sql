SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON people.id = stars.person_id
WHERE name IN ('Jennifer Lawrence', 'Bradley Cooper')
GROUP BY title
HAVING COUNT(DISTINCT name) = 2;