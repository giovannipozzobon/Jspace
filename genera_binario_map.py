# convert a text file to binary file
# this binary file is used for map of titles  
import sys 

def read_values_from_text_file(file_path):
    values = []
    with open(file_path, 'r') as file:
        for line in file:
            # Rimuove spazi bianchi e newline e divide i valori separati da virgole
            stripped_line = line.strip()
            if stripped_line:
                for val_str in stripped_line.split(','):
                    if val_str.strip():  # Verifica se il valore non è una stringa vuota
                        values.append(int(val_str))
    return values


def save_values_to_binary_file(values, output_file_path):
    with open(output_file_path, 'wb') as file:
        for value in values:
            # Scrive ogni valore come unsigned char nel file binario
            file.write(value.to_bytes(1, byteorder='big'))

def main():
    # Verifica che sia stato fornito un file di input
    if len(sys.argv) != 3:
        print("Usage: Inputfile Outputfile")
        sys.exit(1)

    input_file_path = sys.argv[1]
    output_file_path = sys.argv[2]

    print(f"Input file '{input_file_path}'.")
    print(f"Output file '{output_file_path}'.")


    # Legge i valori dal file di testo
    values = read_values_from_text_file(input_file_path)

    # Salva i valori in un file binario
    save_values_to_binary_file(values, output_file_path)

    print(f"I valori sono stati salvati nel file binario '{output_file_path}'.")

if __name__ == "__main__":
    main()
