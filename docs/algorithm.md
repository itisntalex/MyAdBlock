# Algorithme du bloqueur MyAdBlock #

Ce document spécifie l'algorithme régissant le fonctionnement du bloqueur de
publicité MyAdBlock.

Dans un permier temps, voici une version simplfiée de l'algorithme de blocage
de serveur mandataire **MyAdBlock**:

1. **Étape 1**: Lors de la réception d'une requête HTTP en provenance d'un client web, le
   serveur mandataire vérifie dans un premier si la ressource demandée appartient
   l'ensemble des ressources bloquées.
  1. Si la ressources est bloquées alors le mandataire renvoie un message d'erreur
     par l'intermédiaire du protocole HTTP.
  2. Dans le cas contraire, on passe à l'étape 2

2. **Étape 2**: On s'est assuré que la ressource requise n'appartient à aucun
   des fournisseurs censuré, on peut donc envoyer une requête vers le serveur
   cible et attendre sa réponse

3. **Étape 3**: À la réception de la réponse du serveur cible, on retransmet
   cette dernière au client web.
