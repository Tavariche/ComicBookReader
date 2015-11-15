# Git et GitHub

## Commit

* `git init` : Initialiser un répertoire Git
* `git status` : Obtenir le statut du répertoire courant
* `git add fichier.txt` : Ajoute fichier.txt à l'index (avant un commit)
* `git commit -m "Mon message" ` : Effectuer un commit (màj) associé à son message descriptif obligatoire
	* `-am` si déjà ajouté une fois à l'index, évite de répéter `git add`
	* `--amend` pour amender le dernier commit. **Ne Jamais amender un commit présent sur github ! Pose des problèmes au moment du push.**
* Mettre dans le fichier `.gitignore` la liste des fichiers à ignorer

##historique

* `git log` : Voir l'historique des commits
* `git checkout unSha` : Se positionner sur le commit dont on a précisé le sha
* `git checkout main` : Se positionner sur le dernier commit
* `git blame unFichier` : Affiche un historique détaillé des modifs du fichier
* `git show unSha` : Affiche le contenu détaillé d'un commit


*Un commit depuis un état passé supprime les commits qui lui succédaient.*

##Remote

* `git clone URL` : Cloner un repository GitHub situé à l'URL indiquée
* `git push myRemote myBranch` : Envoyer les modifications au remote spécifié dans la branche spécifiée
* `git pull myRemote myBranch` : Récupérer les modifications depuis le remote spécifié dans la branche spécifiée
* Paramétrage du repository :
	* [Générer et ajouter une clé SSH](https://help.github.com/articles/generating-ssh-keys/)
	* [Changer l'URL de son remote (HTTPS -> SSH)](https://help.github.com/articles/changing-a-remote-s-url/)

##Branches

* `git branch` : Affiche les branches du projet ; * devant celle en cours
* `git branch maNouvelleBranche` : Crée une nouvelle branche ; option `-d` pour effacer la branche mentionnée
* `git checkout uneBranche` : Change de branche ; option `-b` pour la créer si inexistante
* `git merge uneBranche` : Fusionne uneBranche avec la branche courrante
	* En cas de conflit, ouvrir le fichier resposable du conflit et résoudre manuellement les problèmes puis commit.
* `git stash` : Mettre de côté le taravil en cours ; retour au dernier commit effectué
	* `git stash pop` : Rétablir le travail en cours en le refusionnant à la branche
