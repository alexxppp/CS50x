select avg(ratings.rating) from ratings, movies where movies.year = 2012 and movies.id = ratings.movie_id;
