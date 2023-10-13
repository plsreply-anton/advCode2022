import sys

def main():
    if len(sys.argv) < 2:
        print("No input file specified, falling back to: day2Input.txt")
        textFile = "day2Input.txt"
    else:
        textFile = sys.argv[1]
        
    hands = {'A': 1, 'B': 2, 'C': 3, 'X': 1, 'Y': 2, 'Z': 3}
    totalScore = 0
    with open(textFile, "r") as file:
        for line in file:
            opponent_choice, your_choice = line.strip().split()  # Split the line into two characters
            totalScore += hands[your_choice]
            if hands[your_choice] == hands[opponent_choice]:
                totalScore += 3  # Draw
            elif (hands[your_choice] == 1 and hands[opponent_choice] == 3) or \
                 (hands[your_choice] == 2 and hands[opponent_choice] == 1) or \
                 (hands[your_choice] == 3 and hands[opponent_choice] == 2):
                totalScore += 6  # You win
            else:
                totalScore += 0  # You lose

    print(f"Total Score: {totalScore}")

if __name__ == "__main__":
    main()
