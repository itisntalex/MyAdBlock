# Analyse des requêtes HTTP avec mandataire #

Dans le cadre d'un accès à une ressource par l'intermédiaire d'un mandataire,
on constate que la procédure nécessite un peu plus de finesse dans l'analyse.

**Remarque**: on peut constater que l'unique intermédiaire du client web est le
mandataire.

1. Dans un premier temps, le client émet sa requête de ressources de la même façon
   qu'en l'absence de mandataire. Seule différence, la requête n'est plus adressée
   au serveur distant disposant de la ressource mais au mandataire.
2. Dans un second temps, le serveur mandataire adresse une réponse au client web,
   à la suite d'un éventuel traitement de sa part de la réponse fournie par le
   serveur distant disposant de la ressource.
3. On recommence les étapes 1 et 2 autant de fois que nécessaire pour acquérir
   l'ensemble des ressources de la page web.
