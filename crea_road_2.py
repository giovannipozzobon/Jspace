

def generate_track(screen_width, track_width, length):
    track = ""
    white_bollard = "W"
    red_bollard = "R"
    grass = "G"
    road = " "


    for i in range(length):
        if i % screen_width == 0:
            track += "\n"  # Vai a capo dopo ogni riga

        if i % screen_width < (screen_width - track_width) / 2 or i % screen_width >= (screen_width + track_width) / 2:
            track += grass + ","  # Esterno verde
        else:
            if i % screen_width < (screen_width - track_width) / 2 + 2 or i % screen_width >= (screen_width + track_width) / 2 - 2:
                if (i // screen_width) % 2 == 0:
                    track += white_bollard + ","
                else:
                    track += red_bollard + ","  # Cordoli rossi e bianchi
            else:
                track += road + ","  # Pista

    return track

def add_curve(track, screen_width, track_width, length):
    border = "B"
    curve = "C"
    curve_start = int((screen_width - track_width) / 2) + 1
    curve_end = int((screen_width + track_width) / 2) - 1

    for i in range(length):
        if (i % screen_width >= curve_start and i % screen_width <= curve_end):
            offset = int((track_width / 2) * (1 - abs((i % screen_width) - (screen_width / 2)) / (screen_width / 2)))
            if (i % screen_width >= curve_start + offset and i % screen_width <= curve_end - offset):
                track += road + ","
            else:
                track += curve + ","
        else:
            track += track[i] + ","

    return track

# Dimensioni dello schermo e della pista
screen_width = 20
track_width = 10
length = 200



# Genera la pista di Formula 1
formula_1_track = generate_track(screen_width, track_width, length)

# Aggiunge curve alla pista
formula_1_track_with_curve = add_curve(formula_1_track, screen_width, track_width, length)

# Salva la rappresentazione della pista con curve su un file di testo
with open("formula_1_track_with_curve.txt", "w") as file:
    file.write(formula_1_track_with_curve)
