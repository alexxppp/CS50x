select avg(songs.energy) from songs, artists where artists.id = songs.artist_id and artists.name = "Drake";
