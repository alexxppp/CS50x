select people.name from people, stars, movies where people.id = stars.person_id and stars.movie_id = movies.id and movies.year = 2004 order by people.birth;
