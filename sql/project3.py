# ----- CONFIGURE YOUR EDITOR TO USE 4 SPACES PER TAB ----- #
import sys,os
sys.path.append(os.path.join(os.path.split(os.path.abspath(__file__))[0], 'lib'))
import pymysql

def connection():
    ''' User this function to create your connections '''    
    con = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='Th@nkotsal!s3812', db='movies') #update with your settings
    
    return con

def updateRank(rank1, rank2, movieTitle):
    try:

        rank1 = float(rank1)
        rank2 = float(rank2)
        if not (0 <= rank1 <= 10 and 0 <= rank2 <= 10):
            return [("status",), ("error",),]
    except ValueError:
        return [("status",), ("error",),]


    con = connection()
    cur = con.cursor()

    try:

        query = "SELECT movie_id, `rank` FROM movie WHERE `title` = %s"

        cur.execute(query, (movieTitle,))
        movies = cur.fetchall()



        if len(movies) != 1:
            return [("status",), ("error",),]

        movie_id, current_rank = movies[0]


        if current_rank is None:
            new_rank = (rank1 + rank2) / 2
        else:
            new_rank = (current_rank + rank1 + rank2) / 3

        update_query = "UPDATE movie SET `rank` = %s WHERE movie_id = %s"
        cur.execute(update_query, (new_rank, movie_id))
        con.commit()

        return [("status",), ("ok",),]
    except Exception as e:
        return [("status",), ("error",),]
    finally:
        cur.close()
        con.close()

def find_actors_who_played_with(actor_id):

    con = connection()
    cur = con.cursor()

    try:

        query_actors = """
        SELECT DISTINCT actor_id 
        FROM role 
        WHERE movie_id IN (SELECT movie_id FROM role WHERE actor_id = %s) 
        AND actor_id != %s
        """
        cur.execute(query_actors, (actor_id, actor_id))
        actors = [row[0] for row in cur.fetchall()]
        
        return actors
    except Exception as e:
        return []
    finally:
        cur.close()
        con.close()
        
def colleaguesOfColleagues(actor_id1, actor_id2):

    actors_c = find_actors_who_played_with(actor_id1)
    if not actors_c:
        return [("status",), ("no results",)]


    actors_d = find_actors_who_played_with(actor_id2)
    if not actors_d:
        return [("status",), ("no results",)]


    con = connection()
    cur = con.cursor()

    try:
        results = []


        for actor_c in actors_c:
            for actor_d in actors_d:
                query_common_movies = """
                SELECT m.title, c.actor_id, d.actor_id 
                FROM movie m, role c, role d
                WHERE m.movie_id = c.movie_id AND m.movie_id = d.movie_id
                AND c.actor_id = %s AND d.actor_id = %s AND c.actor_id != d.actor_id
                """
                cur.execute(query_common_movies, (actor_c, actor_d))
                common_movies = cur.fetchall()
                for movie in common_movies:
                    results.append((movie[0], actor_c, actor_d, actor_id1, actor_id2))

        if not results:
            return [("status",), ("no results",)]

        response = [("title", "actor_c_id", "actor_d_id", "actor_a_id", "actor_b_id")]
        response.extend(results)

        return response
    except Exception as e:
        return [("status",), ("error",)]
    finally:
        cur.close()
        con.close()

def actorPairs(actorId):

    con = connection()
    
    try:

        with con.cursor() as cur:

            cur.execute("""
            SELECT DISTINCT genre_id
            FROM genre
            WHERE genre_id IN (
            SELECT genre_id
            FROM movie_has_genre
            WHERE movie_id IN (
                SELECT movie_id
                FROM role
                WHERE actor_id = %s
            )
            );

            """, (actorId,))
            actor_genres = [row[0] for row in cur.fetchall()]


            if not actor_genres:

                return []

            cur.execute("""
            SELECT r2.actor_id, COUNT(DISTINCT mhg2.genre_id) as genre_count
             FROM role r1, role r2, movie_has_genre mhg2, genre g2
            WHERE r1.movie_id = r2.movie_id
            AND r2.movie_id = mhg2.movie_id
            AND mhg2.genre_id = g2.genre_id
            AND r1.actor_id = %s
            AND r2.actor_id != %s
            GROUP BY r2.actor_id
            HAVING genre_count >= 7;
            """, (actorId, actorId))

            possible_actors = cur.fetchall()




            if not possible_actors:
                return []


            actor_ids = []
            for actor in possible_actors:
                other_actor_id = actor[0]

                cur.execute("""
                    SELECT DISTINCT g.genre_id
                    FROM genre g, movie_has_genre mhg, role r
                    WHERE g.genre_id = mhg.genre_id
                    AND mhg.movie_id = r.movie_id
                    AND r.actor_id = %s
                    AND g.genre_id NOT IN %s;
                """, (other_actor_id, tuple(actor_genres)))
                other_actor_genres = [row[0] for row in cur.fetchall()]




                if all(genre not in actor_genres for genre in other_actor_genres):
                    actor_ids.append((other_actor_id,))


            result = [(actorId,)] + actor_ids

            return result
    finally:

        con.close()


def selectTopNactors(n):

    # Create a new connection
    con=connection()

    # Create a cursor on the connection
    cur=con.cursor()
    query = "SELECT genre_name FROM genre G"
    print (n)
    cur.execute(query)
    genres = cur.fetchall()
    res = [("genreName","actorId","numberOFMovies")] # The list we will return
    #We will run the query for every genre separately 
    for genre in genres:
        query = """SELECT DISTINCT G.genre_name,A.first_name,COUNT(DISTINCT R.movie_id)
          FROM genre G,actor A,movie_has_genre MG,role 
          R WHERE G.genre_id = MG.genre_id AND R.movie_id = MG.movie_id 
          AND R.actor_id = A.actor_id AND G.genre_name = "" %s ""
          GROUP BY A.actor_id 
         ORDER BY COUNT(DISTINCT R.movie_id) DESC"""
        cur.execute(query,genre)
        result = cur.fetchall()
        result = list(result)[:int(n)]
        for x in result:
            res.append(x) #Putting every element in the list
        cur.fetchall()

    cur.close()
    con.close()

    return res

# import queue for the BFS Implementation
from collections import deque

def traceActorInfluence(actorId):
    # Create a new connection
    con=connection()
    # Create a cursor on the connection
    cur=con.cursor()
    # The algorithm makes a BFS Search using the query as a succesor function
    frontier = deque() #Our queue for the BFS
    visited = set() #Hash table to avoid circles
    visited.add(actorId)
    frontier.append(actorId)
    result = []
    while len(frontier) > 0:
        actorId = frontier.popleft() 
        visited.add(actorId)
        query = """
        SELECT DISTINCT B.actor_id
        FROM actor B,movie M1,movie M2,role RA,role RB1,role RB2,
        movie_has_genre MG1,movie_has_genre MG2
        WHERE B.actor_id = RB1.actor_id AND B.actor_id = RB2.actor_id 
        AND RA.actor_id = %s AND M1.movie_id = RA.movie_id AND
        M1.movie_id = RB1.movie_id AND M2.movie_id = RB2.movie_id 
        AND M1.year < M2.year AND M1.movie_id = MG1.movie_id 
        AND MG2.movie_id = M2.movie_id
        """
        cur.execute(query,actorId) 
        children = cur.fetchall() #Extend the node
        for node in children:
            if node not in visited:
                frontier.append(node)
                visited.add(node)
                result.append(node) 
    lst = [("influencedActorId",)]
    lst.extend(result)
    cur.close()
    con.close()
    return lst
