select movies.title, ratings.rating from movies, ratings where movies.year = 2010 and movies.id = ratings.movie_id order by ratings.rating desc, movies.title;
