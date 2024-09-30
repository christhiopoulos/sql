# Αθανάσιος Κότσαλης 1115202200077
# Χρήστος Θειόπουλος 1115202200051
# Ιωάννης Διπλάρης 1115202200041

#1
Select M.title as Title
From movie M, actor A, role R, genre G, movie_has_genre MHG
WHERE (A.actor_id=R.actor_id AND R.movie_id=M.movie_id AND MHG.movie_id=M.movie_id AND MHG.genre_id=G.genre_id)
 AND (A.last_name="Allen" AND G.genre_name="Comedy");

#2

SELECT 
  d.last_name AS last_name,
  m.title AS title
FROM 
  director d,
  movie m,
  movie_has_director md
WHERE 
  md.movie_id = m.movie_id
  AND md.director_id = d.director_id
  AND md.movie_id IN (
    SELECT movie_id FROM role WHERE actor_id IN (
      SELECT actor_id FROM actor WHERE last_name = 'Allen'
    )
  )
  AND md.director_id IN (
    SELECT director_id FROM movie_has_director WHERE movie_id IN (
      SELECT movie_id FROM movie_has_genre GROUP BY movie_id HAVING COUNT(genre_id) >= 2
    )
  )
  ORDER BY d.last_name ASC;

#3 

SELECT DISTINCT X.last_name
FROM  actor X,director Y1,director Y2,movie Q1,movie Q2,movie Q3,
    role R1,role R2,movie_has_genre G1,movie_has_genre G2,
    movie_has_director DQ1,movie_has_director DQ2
WHERE X.last_name = Y1.last_name AND X.actor_id = R1.actor_id AND R1.movie_id = DQ1.movie_id AND DQ1.director_id = Y1.director_id
AND 
X.last_name != Y2.last_name AND X.actor_id = R2.actor_id AND R2.movie_id = DQ2.movie_id AND DQ2.director_id = Y2.director_id
AND G1.movie_id = Q2.movie_id  AND G1.genre_id = G2.genre_id AND G2.movie_id = Q3.movie_id AND 
X.actor_id NOT IN (SELECT X.actor_id FROM actor X,role R WHERE R.actor_id = X.actor_id AND R.movie_id = Q3.movie_id);

#4

SELECT 
    DISTINCT 'yes' AS answer
WHERE EXISTS(
	SELECT * FROM
	movie_has_genre, movie, genre
    WHERE 
    movie_has_genre.movie_id = movie.movie_id 
    AND movie_has_genre.genre_id = genre.genre_id 
    AND genre.genre_name = 'Drama' 
    AND movie.year = 1995
 )
union 
SELECT distinct 'no' AS answer
FROM movie_has_genre, movie, genre
where NOT EXISTS (
	SELECT * FROM
	movie_has_genre, movie, genre
	WHERE
    movie_has_genre.movie_id = movie.movie_id 
    AND movie_has_genre.genre_id = genre.genre_id 
    AND genre.genre_name = 'Drama' 
    AND movie.year = 1995
);

#5

SELECT Distinct
   d1.last_name AS director_1,
   d2.last_name AS director_2
FROM 
    director AS d1,
    director AS d2,
    movie_has_director AS mhd1,
    movie_has_director AS mhd2,
    movie AS m
WHERE
    mhd1.director_id = d1.director_id AND
    mhd2.director_id = d2.director_id AND
    mhd1.movie_id = mhd2.movie_id AND
    mhd1.director_id < mhd2.director_id AND
    m.movie_id = mhd1.movie_id AND
    m.year >= 2000 AND m.year <= 2006 AND
    (
        SELECT COUNT(DISTINCT genre_id)
        FROM movie_has_genre
        WHERE movie_id = mhd1.movie_id
    ) >= 6
ORDER BY
    director_1, director_2;

#6
SELECT DISTINCT X.first_name as actor_name,X.last_name as actor_surname,COUNT(DISTINCT Y.director_id) as count
FROM actor X,director Y,role Z,movie_has_director T

WHERE 
Y.director_id = T.director_id AND Z.movie_id = T.movie_id AND Z.actor_id = X.actor_id AND 
(SELECT COUNT(Q.movie_id)
FROM role Z,movie Q
WHERE Z.actor_id = X.actor_id AND Q.movie_id = Z.movie_id) = 3
GROUP BY X.actor_id;

#7 
SELECT DISTINCT
       MG1.genre_id,COUNT(DISTINCT MHD.director_id) as count
    FROM 
        movie M,movie_has_genre MG1,movie_has_genre MG2,movie_has_director MHD
	WHERE (
	SELECT COUNT(DISTINCT MG.genre_id )
    FROM movie_has_genre MG
    WHERE M.movie_id = MG.movie_id) = 1 AND
    MG1.movie_id = M.movie_id AND MHD.movie_id = MG2.movie_id AND MG2.genre_id = MG1.genre_id
    GROUP BY MG1.genre_id;
    
#8
SELECT r.actor_id
FROM role r, movie_has_genre mhg
WHERE r.movie_id = mhg.movie_id
GROUP BY r.actor_id
HAVING COUNT(DISTINCT mhg.genre_id) = (SELECT COUNT(*) FROM genre);

#9
SELECT DISTINCT X.genre_id AS genre_id_1,Y.genre_id AS genre_id_2,COUNT(DISTINCT D.director_id) AS count
FROM genre X,genre Y,
director D,movie_has_genre MG1,movie_has_genre MG2,
movie_has_director MD1,movie_has_director MD2

WHERE X.genre_id < Y.genre_id AND 
MG1.genre_id = X.genre_id AND MG1.movie_id = MD1.movie_id AND MD1.director_id = D.director_id
AND MG2.genre_id = Y.genre_id AND MG2.movie_id = MD2.movie_id AND MD2.director_id = D.director_id
GROUP BY X.genre_id  ,Y.genre_id

ORDER BY X.genre_id ASC;

#10
SELECT DISTINCT X.genre_id AS genre,Y.actor_id AS actor,COUNT(DISTINCT D.movie_id) AS count
FROM genre X,actor Y,
role D,movie_has_director MD
WHERE X.genre_id < Y.actor_id AND 
MD.movie_id = D.movie_id AND D.actor_id = Y.actor_id AND
NOT EXISTS
(
SELECT MG1.genre_id FROM movie_has_director MD1,movie_has_director MD2,movie_has_genre MG1
WHERE MD1.movie_id = D.movie_id AND MD2.director_id = MD1.director_id  AND MG1.genre_id != X.genre_id
AND MG1.movie_id = MD2.movie_id
) 
GROUP BY X.genre_id  ,Y.actor_id
ORDER BY X.genre_id, Y.actor_id ASC;
