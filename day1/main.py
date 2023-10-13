import sys

def main():
    if len(sys.argv) < 2:
        print("No input file specified, falling back to: day1Input.txt")
        textFile = "day1Input.txt"
    else: 
        textFile = sys.argv[1]
        
    topThree = [0,0,0]
    with open(textFile, "r") as file:
        count = 0 

        # Iterate through each line in the file
        for line in file:
            
            # Check if the line is empty (contains only whitespace)
            if line.strip() == "":
                if count > topThree[-1]:
                    topThree[-1] = count
                count = 0
                topThree.sort(reverse = True)    
            else:
                count += int(line.strip())

    print(f"Elfs with most calories have in total: {topThree[0]+topThree[1]+topThree[2]} cal.")

if __name__ == "__main__":
    main()

    