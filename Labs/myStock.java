import java.io.*;
import java.math.*;
import java.util.*;
//import yahoofinance.*;

// to store the stock name and price
class stockInfo {
	private String name;
	private BigDecimal price;
	public stockInfo(String nameIn, BigDecimal priceIn) {
		name = nameIn; price = priceIn;
	}
	public String toString() {return name + " " + price.toString();}
	public BigDecimal getPrice() {return price;}  //getter for price
}

public class myStock {
	/* 
	 * TODO: declare the data structures used for the database HERE.
	 * HINT: use two data structures to store two copies of the stock information.
	 * One for O(1) retrieval, the other is used to get top K stocks in O(K) time.
	 * HashMap<String, stockInfo> and TreeSet<Map.Entry<String, stockInfo>> are recommended.
	 * The entries are not sorted in HashMap, but they are sorted in TreeSet.
	 */
	
	public myStock() {
		/* 
		 * TODO: implement the constructor to initialize the data structures HERE.
		 * HINT: to let the stocks be sorted by the price in TreeSet data structure 
		 * the compare method need to be overridden. Below is a sample for how it can be done.
		 * https://www.java2novice.com/java-collections-and-util/treeset/comparator-object/ 
The above link is broken. Use the snapshot below:
https://web.archive.org/web/20240305105145/https://www.java2novice.com/java-collections-and-util/treeset/comparator-object/	
		 */
		
	}

	public void insertOrUpdate(String symbol, stockInfo stock) {
		/* 
		 * TODO: implement this method to insert or update the records
		 * Make sure it can be done within O(log(n)) time.
		 * Make sure multiple copies are inserted or updated.
		 * Make sure there aren't records with duplicate symbol
		 * Below links shows how to creat Map.Entry obj which can be inserted to TreeSet<Map.Entry<String, stockInfo>>
		 * https://www.baeldung.com/java-map-new-entry
		 */
		
	}

	public stockInfo get(String symbol) {
		/* 
		 * TODO: implement this method to retrive record from database in O(1) time
		 */
		return null;
	}

	public List<Map.Entry<String, stockInfo>> top(int k) {
		/* 
		 * TODO: implement this method to return the stock records with top k prices in O(k) time
		 * HINT: use iterator to retrive items in the sorted order from a data structure
		 * If you use TreeSet, the Iterator can be created like:
		 * TreeSet<Map.Entry<String, stockInfo>> set = new TreeSet<Map.Entry<String, stockInfo>>;
		 * Iterator<Map.Entry<String, stockInfo>> setIterator = set.iterator();
		 * see more info from https://www.geeksforgeeks.org/treeset-iterator-method-in-java/
		 */
		return null;
	}

	public static void main(String[] args) throws IOException {
		// testing code
		myStock techStock = new myStock();
		BufferedReader reader;
		try {
			reader = new BufferedReader(new FileReader("./US-Tech-Symbols.txt"));
			String line = reader.readLine();
			while (line != null) {
				String[] var = line.split(":");	
				// YahooFinance API is discontinued, so just assign a random value to the stock price.
				int randomValue = (int)(Math.random() * 1001); // Generates a random integer from 0 to 1000
				techStock.insertOrUpdate(var[0], new stockInfo(var[1], new BigDecimal(randomValue)));
				line = reader.readLine();
			}
			reader.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		int i = 1;
		System.out.println("===========Top 10 stocks===========");

		// test the top method
		for (Map.Entry<String, stockInfo> element : techStock.top(10)) {
			System.out.println("[" + i + "]" + element.getKey() + " " + element.getValue());
			i++;
		}

		// test the get method
		System.out.println("===========Stock info retrieval===========");
		System.out.println("VMW" + " " + techStock.get("VMW"));
		System.out.println("BIDU" + " " + techStock.get("BIDU"));
	}
}
