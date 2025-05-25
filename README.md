
# Projet **The Light Corridor**

#### *Date : 2024*
#### *Niveau : M1 S2*
#### *Membres : Hakim AOUDIA, Sylvain TRAN*
#### *Note obtenue : 16.6 / 20*

## Capture d’écran
![image](https://github.com/user-attachments/assets/47428d33-3cfd-4cfd-8a2b-f4d41259137a)

---

## Présentation

**The Light Corridor** est un jeu d’arcade 3D développé en **C++ / OpenGL** pour le cours de Synthèse d’Images.  Le joueur contrôle une raquette qui progresse dans un couloir lumineux : il doit garder la balle devant lui, collecter des bonus et atteindre la fin du niveau sans perdre ses **5 vies**.

Le projet met en œuvre la totalité des notions vues en TP : transformations, éclairage, textures RGBA, collisions physiques, génération procédurale.

---

## Lancement du projet

> **Prérequis :**
>
> * Compilateur **C++17** ou plus
> * **CMake ≥ 3.18**
> * OpenGL ≥ 3.3, **GLFW**, **GLAD**, **GLM**, **stb\_image** (fournis en *submodules*)

```bash
# À la racine du dépôt
$ sh run.sh
```
---

## Fonctionnalités principales

* **Menu principal**, menu *Victoire* et menu *Défaite* entièrement interactifs (souris).
* **Gameplay temps‑réel** : déplacement libre de la raquette + avance dans le couloir.
* **Physique complète** : rebonds balle/murs, balle/raquette, balle/obstacles.
* **Génération procédurale** des obstacles et bonus à chaque niveau.
* **Système de bonus** (3 types) et de score dynamique.
* **Éclairage dynamique** : point‑light suivant la balle & light embarquée caméra.
* **Textures transparentes** (RGBA) pour les vies, HUD et objets bonus.
* **Multi‑niveaux** : un nouveau corridor est généré après chaque victoire.

---


### Contrôles

| Action                           | Entrée                         |
| -------------------------------- | ------------------------------ |
| Naviguer dans les menus          | Souris : clic gauche / molette |
| Quitter le jeu                   | **Q**                          |
| Avancer la raquette              | Maintenir **clic gauche**      |
| Propulser la balle (état collée) | **Clic gauche**                |
| Déplacer la raquette (XY)        | Bouger la **souris**           |

### Types de bonus

| Couleur  | Effet                                                    |
| -------- | -------------------------------------------------------- |
| 🟢 Vert  | Raquette collante : la balle se fixe au prochain contact |
| 🔴 Rouge | +1 vie                                                   |
| 🔵 Bleu  | Agrandit la raquette (limité)                            |
