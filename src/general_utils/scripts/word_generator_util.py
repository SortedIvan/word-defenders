import os

def load_all_words(wordPath):
    clean_words = []
    
    with open(wordPath) as file:
        for line in file:
            if len(line) < 3: # skip words with less than 3 chars
                continue 
            
            

# def overwrite_or_create_actual_word_file():

# def prepend_to_word_file():

# def scramble_word_file():



load_all_words(os.getcwd() + "\\word_repo\\" + "word_dump.txt")