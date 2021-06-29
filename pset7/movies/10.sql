SELECT DISTINCT p.name FROM people p
INNER JOIN directors d ON d.person_id = p.id
INNER JOIN ratings r ON r.movie_id = d.movie_id
WHERE r.rating >= 9.0;