import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class calculator {

	private static int[] speed_sum = new int[500];
	private static double[] flows = new double[500];
	private static long cars_num = 0;

	public static void main(String[] args) {
		BufferedReader reader;
		BufferedWriter writer;
		try {
			reader = new BufferedReader(new FileReader("den_0.2_acc_0.01.txt"));
			writer = new BufferedWriter(new FileWriter("flows_den_0.2_acc_0.01.txt"));
			String line = reader.readLine();
			while (line != null) {
				//System.out.println(line);

				//this line
				String[] words = line.split(" ");
				cars_num++;
				for(int i=0; i<words.length; i++){
					speed_sum[Integer.valueOf(words[0])] += Integer.valueOf(words[3]);
				}

				// read next line
				line = reader.readLine();
			}

			for(int i=0; i<500; i++){
				flows[i] = (double)speed_sum[i] / ((double)cars_num / 500);
				System.out.println(i + " " + flows[i]);
				writer.write(String.valueOf(i) + " " + String.valueOf(flows[i]) + "\n");
			}

			reader.close();
			writer.close();

		} catch (IOException e) {
			e.printStackTrace();
		}



	}
}