select people.name from people, directors, movies, ratings where people.id = directors.person_id and directors.movie_id = movies.id and movies.id = ratings.movie_id and ratings.rating >= 9.0;
