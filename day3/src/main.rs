use std::fs::File;
use std::io::{BufRead, BufReader, Result};

fn char_to_value(c: char) -> i32 {
    match c {
        'a'..='z' => c as i32 - 'a' as i32 + 1,
        'A'..='Z' => c as i32 - 'A' as i32 + 27,
        _ => 0, // Handle other characters
    }
}

fn sort_into_vector(reader: BufReader<File>) -> Result<Vec<String>> {
    let mut counter = 0;
    let mut set = String::new();
    let mut my_vec: Vec<String> = Vec::new();

    for line in reader.lines() {
        let line = line?;

        // Append the line to the current group
        set.push_str(&line);
        set.push('\n');

        counter += 1;

        // Check if it's the third line in the group
        if counter == 3 {
            if set.ends_with('\n') {
                set.pop(); // Remove the last character, which is '\n'
            }
            // Push the accumulated group to the vector
            my_vec.push(set.clone());

            // Reset the counter and the group string
            counter = 0;
            set.clear();
        }
    }
    // If there's a remaining group with fewer than 3 lines, push it to the vector
    if counter > 0 {
        my_vec.push(set);
    }

    Ok(my_vec)
}

fn find_priority(lines: &str) -> Result<i32> {

    let [line1, line2, line3]: [&str; 3] =
        lines.split("\n").collect::<Vec<&str>>().try_into().unwrap();

    let mut total = 0;

    for c in line1.chars() {
        if line2.contains(c) & line3.contains(c) {
            let value = char_to_value(c);
            total += value;
            break
        }
    }
        
    Ok(total)
}

fn part1(filename: &str) -> Result<i32> {
    let mut total = 0; // Declare total as mutable

    // Open the file for reading. Change "your_file.txt" to the path of your file.
    let file = File::open(filename)?;

    // Create a buffered reader for the file.
    let reader = BufReader::new(file);

    // Iterate over the lines and print each line.
    for line in reader.lines() {
        let line = line?;
        let len = line.len();
        let (first_half, second_half) = line.split_at(len / 2);

        for c in first_half.chars() { 
            if second_half.contains(c) {
                let value = char_to_value(c);
                total += value;
                break
            }
        }
    }

    Ok(total)
}

fn part2(filename: &str) -> Result<i32>  {
    let mut total = 0;
    let file = File::open(filename)?;
    let reader = BufReader::new(file);
    let my_vec: Result<Vec<String>> = sort_into_vector(reader);

    for set in my_vec? {
        
        total += find_priority(&set)?;
        
    }
    Ok(total)
}

fn main() -> Result<()> {
    let part1_filename = "day3Input.txt"; // Replace with the actual filename
    let part2_filename = "day3Input.txt"; // Replace with the actual filename

    let total_part1 = part1(part1_filename)?;
    let total_part2 = part2(part2_filename)?;

    println!("Total for Part 1: {}", total_part1);
    println!("Total for Part 1: {}", total_part2);
    

    Ok(())
}

