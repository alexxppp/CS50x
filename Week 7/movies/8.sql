select people.name from people, movies, stars where stars.movie_id = movies.id and movies.title = "Toy Story" and stars.person_id = people.id;
