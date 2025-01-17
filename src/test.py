import turtle

# Configuration de la fenêtre
turtle.setup(800, 600)
turtle.speed(0)
turtle.hideturtle()

# Fonction pour dessiner un rectangle coloré
def draw_rectangle(x, y, width, height, color):
    turtle.penup()
    turtle.goto(x - width / 2, y + height / 2)  # Coin supérieur gauche
    turtle.pendown()
    turtle.fillcolor(color)
    turtle.begin_fill()
    for _ in range(2):
        turtle.forward(width)
        turtle.right(90)
        turtle.forward(height)
        turtle.right(90)
    turtle.end_fill()

# Fonction pour calculer l'IoU et afficher le résultat
def draw_iou(inter_width, inter_height, union_area):
    iou = inter_width * inter_height / union_area if union_area != 0 else 0
    # Affichage du calcul au centre de la surface commune
    turtle.penup()
    turtle.goto(0, 0)
    turtle.color("black")
    turtle.write(f"IoU: {iou:.2f}", align="center", font=("Arial", 16, "bold"))

# Boîte 1
x1, y1, width1, height1 = 60, 50, 100, 30

# Boîte 2
x2, y2, width2, height2 = 90, 50, 100, 30

# Calcul de la surface commune
x_inter_left = max(x1 - width1 / 2, x2 - width2 / 2)
x_inter_right = min(x1 + width1 / 2, x2 + width2 / 2)
y_inter_top = min(y1 + height1 / 2, y2 + height2 / 2)
y_inter_bottom = max(y1 - height1 / 2, y2 - height2 / 2)

if x_inter_left < x_inter_right and y_inter_bottom < y_inter_top:
    # Surface commune existe
    inter_width = x_inter_right - x_inter_left
    inter_height = y_inter_top - y_inter_bottom
    inter_x = (x_inter_left + x_inter_right) / 2
    inter_y = (y_inter_top + y_inter_bottom) / 2

    # Dessiner les parties non communes en rouge
    draw_rectangle(x1, y1, width1, height1, "red")
    draw_rectangle(x2, y2, width2, height2, "red")

    # Dessiner la surface commune en vert
    draw_rectangle(inter_x, inter_y, inter_width, inter_height, "green")

    # Calcul de l'IoU (Union de la surface totale - Surface d'intersection)
    union_area = (width1 * height1) + (width2 * height2) - (inter_width * inter_height)

    # Affichage de l'IoU
    draw_iou(inter_width, inter_height, union_area)
else:
    print("Aucune surface commune entre les deux boîtes.")

turtle.done()
