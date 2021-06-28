SELECT AVG(s.energy) AS average_energy FROM songs s
INNER JOIN artists a ON a.id = s.artist_id
WHERE a.name = "Drake";