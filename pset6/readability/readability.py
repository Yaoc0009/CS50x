from cs50 import get_string


def main():
    
    # Track counts
    count = {
        "letters": 0,
        "words": 1,
        "sentences": 0
    }
    
    # Get string input
    s = get_string("Text: ")
    
    # Count PoS
    for c in s:
        if c.isalpha():
            count["letters"] += 1
        elif c == " ":
            count["words"] += 1
        elif c in [".", "!", "?"]:
            count["sentences"] += 1
    		
    # Coleman-Liau index
    L = count["letters"] / count["words"] * 100
    S = count["sentences"] / count["words"] * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    
    # Print index results
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")
    	
    	
if __name__ == "__main__":
    main()