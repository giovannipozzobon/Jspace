import math

# Funzione per disegnare una sezione di strada
def drawRoadSection(width, color):
    return [color for _ in range(int(width))]

# Funzione principale
def main():
    roadLength = 50  # lunghezza della strada
    screen_width = 20  # larghezza dello schermo
    roadWidth = screen_width - 10  # larghezza della strada
    curbWidth = 2   # larghezza dei cordoli
    output = []

    # Disegna la strada
    for i in range(roadLength):
        # Calcola la posizione della strada per creare una curva
        roadPosition = roadWidth // 2 * (math.sin(i / 10.0) + 1)

        # Alterna tra cordoli rossi e bianchi
        curbColor = 'R' if i % 2 == 0 else 'W'

        # Disegna la strada con la posizione calcolata
        output.extend(drawRoadSection(roadPosition - curbWidth, ' '))
        output.extend(drawRoadSection(curbWidth, curbColor))
        output.extend(drawRoadSection(roadWidth - 2 * curbWidth, 'N'))
        output.extend(drawRoadSection(curbWidth, curbColor))
        output.extend(drawRoadSection(roadWidth - roadPosition - curbWidth, ' '))

        # Disegna il prato
        output.extend(drawRoadSection(screen_width - roadWidth, 'P'))

        # Va a capo ogni 20 caratteri
        if (i + 1) % screen_width == 0:
            output.append('\n')

    # Unisce tutti i caratteri in una stringa separata da virgole
    output_str = ','.join(output)
    
    # Salva l'output su un file di testo
    f = open('output.txt', 'w')
    f.write(output_str)
    f.close()

    return output_str

print(main())
print("The output has been saved to output.txt")