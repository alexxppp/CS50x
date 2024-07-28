select count(movies.title) from movies, ratings where movies.id = ratings.movie_id and ratings.rating = 10.0;
