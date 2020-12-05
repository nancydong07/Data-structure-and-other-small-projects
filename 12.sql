--In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
--Your query should output a table with a single column for the title of each movie.
--You may assume that there is only one person in the database with the name Johnny Depp.
--You may assume that there is only one person in the database with the name Helena Bonham Carter.

SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars JOIN people on people.id = stars.person_id where name = "Helena Bonham Carter") AND id IN (SELECT movie_id FROM stars JOIN people on people.id = stars.person_id where name = "Johnny Depp")