import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

class AoC {
    private ArrayList<String> listPair = new ArrayList<>();

    public void getPair()
    {
        BufferedReader reader;
        
		try {
			reader = new BufferedReader(new FileReader("day4Input.txt"));
			String line = reader.readLine();

			while (line != null) {
				//System.out.println(line);
				listPair.add(line);
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
    }

    public ArrayList<Integer> getInt(String string)
    {
        String[] temp = string.split("-");
        ArrayList<Integer> intTemp = new ArrayList<>();
        for (String string2 : temp) {
            intTemp.add(Integer.valueOf(string2));
        }
        return intTemp;
    }

    public int compare()
    {
        int counter = 0;
        for (String string : listPair) {
            String[] temp = string.split(",");
            ArrayList<Integer> first = getInt(temp[0]);
            ArrayList<Integer> second = getInt(temp[1]);

            if (first.get(0) >= second.get(0) & first.get(1)<= second.get(1)) {
                counter += 1;
            } else if (first.get(0) <= second.get(0) & first.get(1) >= second.get(1)) {
                counter += 1;
            }
        }
        return counter;
    }

    public int comparePart2()
    {
        int counter = 0;
        for (String string : listPair) {
            String[] temp = string.split(",");
            ArrayList<Integer> first = getInt(temp[0]);
            ArrayList<Integer> second = getInt(temp[1]);
            
            if (second.get(1) >= first.get(1)) {
                if (first.get(0) >= second.get(0) || first.get(1) >= second.get(0)) {
                    counter += 1;
                }
            } else {
                if (second.get(0) >= first.get(0) || second.get(1) >= first.get(0)) {
                    counter += 1;
                }
            }
        }
        return counter;
    }

    public static void main(String[] args) {
        AoC AoC= new AoC();
	    AoC.getPair();

        int counter = AoC.compare();
        System.out.println("Total for part 1: " + counter);

        int counter2 = AoC.comparePart2();
        System.out.println("Total for part 2: " + counter2);   
	}
}