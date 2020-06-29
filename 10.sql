--In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
--Your query should output a table with a single column for the name of each person.
 SELECT DISTINCT name FROM people JOIN directors on people.id = directors.person_id JOIN movies on movies.id = directors.movie_id JOIN ratings ON movies.id = ratings.movie_id WHERE rating >= 9
--SELECT name FROM people WHERE people.id IN (SELECT person_id FROM stars JOIN people on people.id = stars.person_id JOIN movies on movies.id = stars.movie_id WHERE year = 2004) ORDER BY birth ASC
