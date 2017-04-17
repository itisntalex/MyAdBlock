# Analyse des requêtes HTTP sans mandataire #

Dans le cas où l'on utilise pas de serveur mandataire, l'ensemble des requêtes
HTTP utilisées pour accéder à la ressource est relativement simple.

1. Le client web (Google Chrome, Mozilla Firefox, etc...) envoie une requête
   `GET` au serveur destant disposant de la ressource à laquelle on souhaite
   accéder.
2. Le serveur renvoie sa réponse directement au client web, qu'il s'agisse d'un
   succès ou d'un échec.
3. Le client web repête les deux opérations précédentes pour chaque ressources
   requise par la page web.
