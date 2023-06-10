# Shootem-up

## Présentation
Ce jeu a été développé par **DJEBLOUN Yacine** et **RODDIER Corentin** dans le cadre d'un projet informatique donné dans l'enseignement **Programmation en C**. Ce jeu n'a pas été fait dans un but commercial et peut contenir des images non libres de droits.

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
![Menu principal](data/img/menu_doc.png)
> Ecran du menu principal

Vous avez le choix entre 3 options :
- Jouer : vous permet de lancer une partie de Shootem-up
- Crédits : vous permet de voir les crédits du jeu
- Quitter : vous permet de quitter le jeu

### En jeu
Une fois la partie lancée, vous arriverez sur une page ressemblant à celle-ci :
![En jeu](data/img/game_doc.png)
> Ecran de jeu

Une fois sur cet écran, le jeu est lancé et vous pouvez vous déplacer avec les touches directionnelles de votre clavier. Vous avez également la possibilité de tirer des projectiles avec la touche `espace` sur les ennemis qui vont arriver vers vous. Plus votre score augmente, plus le jeu devient difficile : les ennemis sont plus nombreux et ont plus de points de vie. Tous les 500 points, un bonus ou un malus apparait. Vous pouvez les récupérer en vous déplaçant dessus.
Les bonus suivants vous permettent de :<br/>
![Bonus de vie](data/img/bonus/health.png) : regagner 1 point de vie<br/>
![Bouclier](data/img/bonus/shield.png) : protéger de 3 projectiles ennemis<br/>
![Bonus de vitesse](data/img/bonus/speed.png) : augmenter votre vitesse de 2 points<br/>
![Bonus de bombe](data/img/bonus/bomb.png) : tuer l'ensemble des ennemis présents sur la page<br/>
![Bonus de bombe](data/img/bonus/attack.png) : améliorer d'un point les dégâts de vos projectiles <br/>
Les malus suivants vous infligent : <br/>
![Malus inversement touche](data/img/penalty/reverse.png) : un inversement des touches directionnelles <br/>
![Malus de vitesse](data/img/penalty/slow.png) : une perte de 5 points de vitesse (limité à 5 de vitesse minimum)<br/>
![Malus de vague](data/img/penalty/damage.png) : à vous de le découvrir...<br/>