import string

def is_palindrome_from_file(filename):
    try:
        # Step 1: Read the entire content of the file
        with open(filename, 'r', encoding='utf-8') as file:
            text = file.read()
        
        # Step 2: Lowercase the text
        text = text.lower()

        # Step 3: Remove newlines and keep only letters
        cleaned = ''.join(char for char in text if char in string.ascii_letters)

        # Step 4: Check if it's a palindrome
        return cleaned == cleaned[::-1]

    except FileNotFoundError:
        print(f"File '{filename}' not found.")
        return False

# Example usage:
filename = "input.txt"  # Replace with your actual file name
if is_palindrome_from_file(filename):
    print("The file content is a palindrome.")
else:
    print("The file content is NOT a palindrome.")

