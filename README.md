# Shootem-up

## Présentation
Ce jeu a été développé par DJEBLOUN Yacine et RODDIER Corentin dans le cadre d'un projet informatique donné dans l'enseignement `Programmation en C`. Ce jeu n'a pas été fait dans un but commercial et peut contenir des images non libres de droits.

## Compilation
Pour compiler le jeu : `make`

Pour lancer le jeu : `make run`

## Logs github
Pour générer les logs github : `git log --pretty=format:"%cs (%an): %s" >> logs.txt`

## Documentation Doxygen
Pour générer la documentation : ``doxygen Doxygen``

## Utilisation
### Menu principal
En lancant le jeu, vous arriverez sur une page ressemblant à celle-ci :
![Menu principal](https://cdn.discordapp.com/attachments/1107558985785167894/1114273161891037245/Menu_game.png)
> Ecran du menu principal

Vous avez le choix entre 3 options :
- Jouer : vous permet de lancer une partie de Shootem-up
- Crédits : vous permet de voir les crédits du jeu
- Quitter : vous permet de quitter le jeu

### En jeu
Une fois la partie lancée, vous arriverez sur une page ressemblant à celle-ci :
![En jeu](https://cdn.discordapp.com/attachments/1107558985785167894/1114276491170160770/jeu_dofus.png)
> Ecran de jeu

Une fois sur cet écran, le jeu est lancé et vous pouvez vous déplacer avec les touches directionnelles de votre clavier. Vous avez également la possibilité de tirer des projectiles avec la touche `espace` sur les ennemis qui vont arriver vers vous. Plus votre score augmente, plus le jeu devient difficile : les ennemis sont plus nombreux et ont plus de points de vie. Tous les 500 points, un bonus ou un malus apparait. Vous pouvez les récupérer en vous déplaçant dessus.
Les bonus sont les suivants :
![Bonus de vie](https://media.discordapp.net/attachments/1107558985785167894/1114279616312508567/health.png) : vous permet de récupérer 1 point de vie<br/>
![Bouclier](https://media.discordapp.net/attachments/1107558985785167894/1114279617172348988/shield.png) : vous permet de récupérer un bouclier qui vous protège de 3 projectiles ennemis<br/>
![Bonus de vitesse](https://media.discordapp.net/attachments/1107558985785167894/1114279617591783585/speed.png) : vous permet de récupérer un bonus de vitesse pendant
![Bonus de bombe](https://media.discordapp.net/attachments/1107558985785167894/1114279618019598456/bomb.png) : vous permet de récupérer une bombe qui détruit tous les ennemis à l'écran<br/>
Les malus sont les suivants :
![Malus inversement touche](https://media.discordapp.net/attachments/1107558985785167894/1114284993276035152/reverse.png) : inverse les touches directionnelles<br/>
![Malus de vitesse](https://media.discordapp.net/attachments/1107558985785167894/1114284993674485760/slow.png) : vous ralentit<br/>
![Malus de vague](https://media.discordapp.net/attachments/1107558985785167894/1114284994454638682/damage.png) : fait apparaitre une vague de 10 ennemis<br/>