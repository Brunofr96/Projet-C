import tkinter as tk
from tkinter import filedialog, messagebox
import subprocess  # Permet d'exécuter des commandes système
import os  # Fournit des fonctions pour interagir avec le système de fichiers

# Fonction pour ajouter un texte d'aide grisé (placeholder)
def add_placeholder(event=None):
    if text_input.get("1.0", tk.END).strip() == "":
        text_input.insert(tk.END, placeholder_text)  # Ajoute le texte d'aide
        text_input.tag_add("placeholder", "1.0", tk.END)  # Applique le style "placeholder"
        text_input.tag_configure("placeholder", foreground="gray")  # Définit la couleur grise

# Fonction pour retirer le placeholder quand l'utilisateur commence à écrire
def remove_placeholder(event=None):
    if text_input.get("1.0", tk.END).strip() == placeholder_text:
        text_input.delete("1.0", tk.END)  # Supprime le texte d'aide

# Fonction pour ouvrir un fichier
def open_file():
    filepath = filedialog.askopenfilename(defaultextension=".draw", filetypes=[("DrawPlus Files", "*.draw"), ("All Files", "*.*")])
    if filepath:
        with open(filepath, "r") as file:
            content = file.read()  # Lit le contenu du fichier
            text_input.delete("1.0", tk.END)  # Supprime le texte actuel
            text_input.insert(tk.END, content)  # Ajoute le contenu du fichier
            root.title(f"DrawPlus Interface - {os.path.basename(filepath)}")  # Met à jour le titre de la fenêtre

# Fonction pour sauvegarder un fichier
def save_file():
    filepath = filedialog.asksaveasfilename(defaultextension=".draw", filetypes=[("DrawPlus Files", "*.draw"), ("All Files", "*.*")])
    if filepath:
        with open(filepath, "w") as file:
            file.write(text_input.get("1.0", tk.END).strip())  # Sauvegarde le contenu
        root.title(f"DrawPlus Interface - {os.path.basename(filepath)}")  # Met à jour le titre

# Fonction pour créer un nouveau fichier
def new_file():
    text_input.delete("1.0", tk.END)  # Vide la zone de texte
    root.title("DrawPlus Interface - Nouveau fichier")  # Réinitialise le titre

# Fonction pour exécuter les instructions entrées
def run_process():
    instructions = text_input.get("1.0", tk.END).strip()  # Récupère le texte saisi
    if instructions:
        try:
            # Crée un fichier temporaire contenant les instructions
            with open("input.temp", "w") as f:
                f.write(instructions)
            
            # Exécute le programme C avec le fichier temporaire
            result = subprocess.run(["./drawplus", "input.temp"], capture_output=True, text=True)

            # Affiche les résultats du programme C dans la zone Output
            output_text.delete("1.0", tk.END)
            output_text.insert(tk.END, result.stdout)
            
            if result.returncode != 0:  # Vérifie si une erreur est survenue
                output_text.insert(tk.END, "\nErreur lors de la génération du fichier Python.")
                return

            os.remove("input.temp")  # Supprime le fichier temporaire
            
            # Exécute le script Python généré
            dessin_path = "output/dessin.py"
            if os.path.exists(dessin_path):
                subprocess.run(["python", dessin_path])
            else:
                output_text.insert(tk.END, "\nLe fichier 'dessin.py' n'a pas été trouvé.")
        except Exception as e:
            messagebox.showerror("Erreur", f"Une erreur est survenue : {e}")
    else:
        output_text.insert(tk.END, "Veuillez entrer des instructions.\n")

# Fonction pour valider les instructions (exemple simple)
def validate_instructions():
    instructions = text_input.get("1.0", tk.END).strip()
    text_input.tag_remove("error", "1.0", tk.END)  # Supprime les anciens tags d'erreur
    text_input.tag_remove("fix", "1.0", tk.END)  # Supprime les anciens tags de correction
    
    # Vérifie si certaines instructions clés sont manquantes (exemple simplifié)
    if "circle" not in instructions:
        text_input.tag_add("error", "1.0", "1.5")
        text_input.tag_configure("error", background="red")
    
    if "line" not in instructions:
        text_input.tag_add("fix", "1.0", "1.5")
        text_input.tag_configure("fix", foreground="green")

# Fonction pour surligner les mots-clés dans le texte
def highlight_keywords():
    keywords = ["circle", "line", "square", "color", "advance", "left", "right", "orientTo", "resetPosition", "triangle"]
    text_input.tag_remove("keyword", "1.0", tk.END)  # Supprime les anciens tags
    for keyword in keywords:
        start_pos = "1.0"
        while True:
            start_pos = text_input.search(keyword, start_pos, stopindex=tk.END, nocase=True)  # Recherche du mot-clé
            if not start_pos:
                break
            end_pos = f"{start_pos}+{len(keyword)}"  # Calcule la position de fin
            text_input.tag_add("keyword", start_pos, end_pos)  # Ajoute un tag
            start_pos = end_pos
        text_input.tag_configure("keyword", foreground="green")  # Définit la couleur verte

# Configuration de la fenêtre principale
root = tk.Tk()
root.title("DrawPlus Interface")

# Menu
menu_bar = tk.Menu(root)
root.config(menu=menu_bar)

file_menu = tk.Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Fichier", menu=file_menu)
file_menu.add_command(label="Nouveau", command=new_file)
file_menu.add_command(label="Ouvrir", command=open_file)
file_menu.add_command(label="Sauvegarder", command=save_file)
file_menu.add_separator()
file_menu.add_command(label="Quitter", command=root.quit)

# Zone de texte pour entrer les instructions
tk.Label(root, text="Instructions :").pack(anchor="w")
text_input = tk.Text(root, height=25, width=50)
text_input.pack()

# Placeholder text (texte d'aide grisé)
placeholder_text = """# Exemple : cercle avec centre à (100, 100), rayon 50, et un déplacement horizontal de 100 unités
# Exemple : ligne de (0, 100) à (100, 100)
# Exemple : carré avec coin supérieur gauche à (200, 200), taille de côté 100, et déplacement horizontal de 20 unités"""

add_placeholder()  # Ajout initial du placeholder
text_input.bind("<KeyPress>", remove_placeholder)  # Supprime le placeholder dès la première saisie
text_input.bind("<KeyRelease>", lambda event: validate_instructions())  # Valide les instructions après chaque saisie

# Bouton pour exécuter les instructions
run_button = tk.Button(root, text="Run", command=run_process)
run_button.pack()

# Zone de texte pour les résultats ou erreurs
tk.Label(root, text="Output :").pack(anchor="w")
output_text = tk.Text(root, height=10, width=50)
output_text.pack()

highlight_keywords()  # Met en surbrillance les mots-clés dès le lancement

# Lancement de la boucle principale Tkinter
root.mainloop()
