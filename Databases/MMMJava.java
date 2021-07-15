import java.util.Scanner;
import java.sql.*;

public class MMMJava {
	//This method is for running all the customer use cases
	static void runCustomer() {
		Connection c = null;
		Statement stmt = null;
		Scanner scan = new Scanner(System.in);
		String option;
		boolean newCustomer = false;
		int custID = 0;
		int [] productID = new int[10];
		int [] distID = new int[10];
		
		//Gets the customer's name
		String name;
		boolean foundName = false;
		System.out.println("Please enter your first and last names: ");
		name = scan.nextLine();
		System.out.println("Checking the system....");
		
		//This will keep looping until the user either quits, decides to make an new profile, or enters a valid name
		while(!foundName) {
			//TO DO: Check the database for the customer name
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);

			      stmt = c.createStatement();
			      String sql = "SELECT cust_ID FROM Customer WHERE cust_name = '" + name + "'";
			      //System.out.println(sql);
			      ResultSet rs = stmt.executeQuery(sql);
			      while ( rs.next() ) {
			    	  custID = rs.getInt("cust_ID");
				      
			    	  foundName = true;
			      }
			      rs.close();
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
			
			if(foundName) {
				break;
			}
			else {
				System.out.println("The name " + name + " is not a part of the system. What would you like to do?");
				System.out.println("[1]Create a profile\t[2]Enter a different name");
				option = scan.next();
		
				while(!option.equals("1") && !option.equals("2") && !option.equalsIgnoreCase("q")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				
				//If the user wants to create a new profile
				if(option.equals("1")) {
					boolean correctInput = false;
					while(!correctInput) {
						System.out.println("Enter your first and last names: ");
						scan.nextLine();
						name = scan.nextLine();
						System.out.println("Enter your street name/house number: ");
						String street = scan.nextLine();
						System.out.println("Enter your zip code: ");
						String zip = scan.next();
						System.out.println("Enter your city name: ");
						String city = scan.next();
						System.out.println("Enter your phone number: ");
						String phoneNumber = scan.next();
						System.out.println("Enter your age: ");
						String age = scan.next();
						int random = (int)(Math.random()*(1000)+1);
						
						System.out.println();
						System.out.println("Does this information look correct?");
						System.out.println("Name: " + name);
						System.out.println("Address: " + street + " " + zip + " " + city + " CA");
						System.out.println("City: " + city);
						System.out.println("Phone number: " + phoneNumber);
						System.out.println("Age: " + age);
						System.out.println("[1]Yes\t[2]No");
						option = scan.next();
						
						
						while(!option.equals("1") && !option.equals("2") && !option.equalsIgnoreCase("q")) {
							System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
							option = scan.next();
						}
						
						//If the data is correct, add this user to the system
						if(option.equals("1")) {
							//TO DO: add this user to the system!
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);
							      int cityID = 0;

							      stmt = c.createStatement();
							      String sql = "SELECT city_ID FROM city WHERE city_name = '" + city + "'";
							      ResultSet rs1 = stmt.executeQuery(sql);
							      while ( rs1.next() ) {
							    	  cityID = rs1.getInt("city_ID");
							      }
							      rs1.close();
							      
							      sql = "INSERT INTO Customer VALUES(" + random + ", '" + name + "', '"+ street + "', "+ cityID + ", " + zip + ", " + phoneNumber + ", " + age + ");";
							      stmt.executeUpdate(sql);
							      //System.out.println(sql);
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							      System.exit(0);
							   }
							
							newCustomer = true; //Used to give a discount later for first-time purchase
							System.out.println("Your profile was created successfully!");
							custID = (int)random;
							foundName = true;
							correctInput = true; //Breaks out of the loop
							
							
						}
						else if(option.equalsIgnoreCase("q")) {
							System.out.println("Thank you, goodbye!");
							System.exit(0);
						}
						
						//Option = 2, so the values are not correct
						else {
							//Goes back to the beginning of the loop so the user can re-enter the right values.
							System.out.println("Please re-enter the correct data.");
						}
					}
				}
			}
		}

		//If we get to here the customer has a profile and can continue
		System.out.println();
		System.out.println("Hello, " + name + "! What would you like to do?");
		System.out.println("[1]Browse Products\t[2]Update Profile");
		option = scan.next();
		
		while(!option.equals("1") && !option.equals("2") && !option.equalsIgnoreCase("q")) {
			System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
			option = scan.next();
		}
		
		//The customer wants to browse the products NOTE: this section also includes leaving reviews
		if(option.equals("1")) {
			boolean purchasing = false;
			double maxPrice = 0;
			while(!purchasing) {
				boolean hasMaxPrice = false;
				String type;
				String strain;
				
				//Asks for the type that they want
				System.out.println();
				System.out.println("What type of product do you want to look for?");
				System.out.println("[1]Flower\t[2]Edible\t[3]Cartridge\t[4]All");
				option = scan.next();
				while(!option.equals("1") && !option.equals("2") && !option.equals("3") && !option.equals("4")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				if(option.equals("1"))
					type = "flower";
				else if(option.equals("2"))
					type = "edible";
				else if(option.equals("3"))
					type = "cartridge";
				else
					type = "all";
				
				//Asks for the strain that they want
				System.out.println();
				System.out.println("What type of strain do you want to look for?");
				System.out.println("[1]Sativa\t[2]Sativa dominant hybrid\t[3]Indica dominant hybrid\t[4]All");
				option = scan.next();
				while(!option.equals("1") && !option.equals("2") && !option.equals("3") && !option.equals("4")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				if(option.equals("1"))
					strain = "sativa";
				else if(option.equals("2"))
					strain = "sativa dominant hybrid";
				else if(option.equals("3"))
					strain = "indica dominant hybrid";
				else
					strain = "all";
				
				System.out.println();
				System.out.println("Do you want to enter a maximum price?\n[1]Yes\t[2]No");
				option = scan.next();
				while(!option.equals("1") && !option.equals("2")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				
				if(option.equals("1")) {
					System.out.println("Please enter the maximum price you are willing to spend: ");
					maxPrice = scan.nextDouble();
					hasMaxPrice = true;
					
				}
				
				System.out.println("-------------------------------------------------------------------------------------");
				//Output the products!
				if(hasMaxPrice) {
					//Outputs the products, with a max price!
					
					//TO DO: Output the products
					if(type.equals("all")) {
						//The customer wants to look at all types of products, with a max price
						     
						
						if(strain.equals("all")) {
							//The customer wants to look at all types of strains and all types of products, with a max price
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE p_cost < " + maxPrice;
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							   }
						}
						else {
							//The customer wants to look at all types of products and one type of strain, with a max price
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE p_cost < " + maxPrice + " AND p_strain = '" + strain + "'";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
						}
					}
					}
					else {
						//The customer wants to look at just one type of product
						if(strain.equals("all")) {
							//The customer wants to look at all types of strains and one type of product, with a max price
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE maxPrice < " + maxPrice + " AND p_type = '" + type + "'";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							   }
						}
						else {
							//The customer wants to look at one type of product and one type of strain, with a max price
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE maxPrice < " + maxPrice + " AND p_type = '" + type + "' AND p_strain = '" + strain + "';";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							   }
						}
					}
				}
				else {
					//The customer did not set a max price
					if(type.equals("all")) {
						//The customer wants to look at all types of products
						
						if(strain.equals("all")) {
							//The customer wants to look at all types of strains and all types of products
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							   }
						}
						else {
							//The customer wants to look at all types of products and one type of strain
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE p_strain = '" + strain + "'";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
						}
						}
					}
					else {
						//The customer wants to look at just one type of product
						if(strain.equals("all")) {
							//The customer wants to look at all types of strains and one type of product
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE p_type = '" + type + "'";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
						}
						}
						else {
							//The customer wants to look at one type of product and one type of strain
							try {
							      Class.forName("org.sqlite.JDBC");
							      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
							      c.setAutoCommit(false);

							      stmt = c.createStatement();
							      String sql = "SELECT p_ID, p_name, p_scale, p_type, p_effects, p_strain, p_cost FROM Product WHERE p_type = '" + type + "' AND p_strain = '" + strain + "'";
							      //System.out.println(sql);
							      ResultSet rs = stmt.executeQuery(sql);
							      while ( rs.next() ) {
							    	  int ID = rs.getInt("p_ID");
							    	  String prodName = rs.getString("p_name");
							    	  double scale = rs.getDouble("p_scale");
							    	  String prodType = rs.getString("p_type");
							    	  String effects = rs.getString("p_effects");
							    	  String strain1 = rs.getString("p_strain");
							    	  double cost = rs.getDouble("p_cost");
							    	  
							    	  System.out.println("[" + ID + "]" + prodName + "\nScale: " + scale + "\nType: " + prodType + "\nStrain: " + strain1);
							    	  System.out.println("Effects "+ effects + "\nPrice: $" + cost);
							    	  System.out.println("-------------------------------------------------------------------------------------");
							      }
							      rs.close();
							      stmt.close();
								  c.close();
							   } catch ( Exception e ) {
							      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
							   }
						}
					}
				}
				
				System.out.println("What would you like to do?\n[1]Make a purchase\t[2]Browse different products\t[3]Leave a review\t[Q]Quit");
				option = scan.next();
				while(!option.equals("1") && !option.equals("2") && !option.equals("3") && !option.equalsIgnoreCase("q")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				if(option.equals("1")) {
					//The customer wants to make a purchase
					purchasing = true; //Breaks out of the loop
					
				}
				else if(option.equals("3")) {
					int reviewProductID;
					System.out.println("Please enter the name of the ID you want to leave a review for: ");
					reviewProductID = scan.nextInt();
					
					boolean exists = false;
					//TO DO: Check if this product exists in the database
					try {
					      Class.forName("org.sqlite.JDBC");
					      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
					      c.setAutoCommit(false);

					      stmt = c.createStatement();
					      String sql = "SELECT p_ID FROM Product WHERE p_ID = " + reviewProductID;
					      //System.out.println(sql);
					      ResultSet rs = stmt.executeQuery(sql);
					      while ( rs.next() ) {
					    	exists = true;
						  }
					      rs.close();
					      stmt.close();
						  c.close();
					   } catch ( Exception e ) {
					      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
					      System.exit(0);
					   }
					
					//If the product is not in the database
					while(!exists) {
						System.out.println("This product does not exist!");
						System.out.println("Please enter the ID of the product you want to leave a review for: ");
						reviewProductID = scan.nextInt();
						//TO DO: Check if this product exists in the database
						try {
						      Class.forName("org.sqlite.JDBC");
						      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
						      c.setAutoCommit(false);

						      stmt = c.createStatement();
						      String sql = "SELECT p_ID FROM Product WHERE p_ID = " + reviewProductID;
						      //System.out.println(sql);
						      ResultSet rs = stmt.executeQuery(sql);
						      while ( rs.next() ) {
						    	//Get the data for the customer here, including their ID number  
							  }
						      rs.close();
						      stmt.close();
							  c.close();
						   } catch ( Exception e ) {
						      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
						      System.exit(0);
						   }
					}
					
					String review;
					int rating;
					System.out.println("Enter the rating you want to give this product, from 1 to 5: ");
					rating = scan.nextInt();
					System.out.println("Please enter a short description of your review: ");
					scan.nextLine();
					review = scan.nextLine();
					
					//TO DO: Input the customer's review of a product
					try {
					      Class.forName("org.sqlite.JDBC");
					      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
					      c.setAutoCommit(false);
					      //System.out.println("Opened database successfully");

					      stmt = c.createStatement();
					      String sql = "INSERT INTO ProductReview VALUES(" + custID + ", " + "00000, " + reviewProductID + ", " + rating + ", '" + review + "');";
					      //System.out.println(sql);
					      stmt.executeUpdate(sql);
					}
					   catch ( Exception e ) {
					      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
					      System.exit(0);
					   }
					
					System.out.println("Thank you for your review!");
					System.out.println("Would you like to keep browsing products?");
					System.out.println("[1]Yes\t[2]No");
					option = scan.next();
					if(option.equals("2")) {
						System.out.println("Thank you, goodbye!");
						System.exit(0);
					}
					
				}
				else if(option.equalsIgnoreCase("q")) {
					System.out.println("Thank you, goodbye!");
					System.exit(0);
				}
			}
			
			
			//If we have gotten to this point then the customer has browsed the products and wants to make a purchase
			int i = 0;
			while(purchasing) {
				System.out.println("Please enter the ID of the product you want to purchase: ");
				productID[i] = scan.nextInt();
				boolean exists = false;
				//TO DO: Check if this product exists in the database
				try {
				      Class.forName("org.sqlite.JDBC");
				      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
				      c.setAutoCommit(false);
				      //System.out.println("Opened database successfully");

				      stmt = c.createStatement();
				      String sql = "SELECT p_ID, p_dist_ID FROM Product WHERE p_ID = " + productID[i];
				      //System.out.println(sql);
				      ResultSet rs = stmt.executeQuery(sql);
				      while ( rs.next() ) {
					      distID[i] = rs.getInt("p_dist_ID");
				    	  exists = true;
				      }
				      rs.close();
				      stmt.close();
					  c.close();
				   } catch ( Exception e ) {
				      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
				      System.exit(0);
				   }
			
				//If the product is not in the database
				while(!exists) {
					System.out.println("This product does not exist!");
					System.out.println("Please enter the ID of the product you want to purchase: ");
					productID[i] = scan.nextInt();
					//TO DO: Check if this product exists in the database
					try {
					      Class.forName("org.sqlite.JDBC");
					      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
					      c.setAutoCommit(false);

					      stmt = c.createStatement();
					      String sql = "SELECT p_ID FROM Product WHERE p_ID, p_dist_ID = " + productID[i];
					      //System.out.println(sql);
					      ResultSet rs = stmt.executeQuery(sql);
					      while ( rs.next() ) {
					    	  distID[i] = rs.getInt("p_dist_ID");
					    	  exists = true;
					      }
					      rs.close();
					      stmt.close();
						  c.close();
					   } catch ( Exception e ) {
					      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
					      System.exit(0);
					   }
				}
				i++;
				System.out.println("Would you like to add another product to your purchase?\n[1]Yes\t[2]No");
				option = scan.next();
				if(option.equals("2")) {
					purchasing = false; //Breaks out of the loop
				}
			}
			double price1 = 0;
			System.out.println();
			//TO DO: Check if there is a deal of the day or a discount for a new customer, and then output the total price of all the products
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);
			      double discount = 0;
			      if(newCustomer) {
			    	  System.out.println("Since you are a new customer, you get 30% off your purchase!");
			    	  discount = .3;
			      }
			      else {
			    	  System.out.println("You have qualified for 10% off from our deal of the day!");
			    	  discount = .1;
			      }
			      stmt = c.createStatement();
			      String sql = "SELECT SUM(DISTINCT p_cost) FROM product WHERE p_ID = " + productID[0];
			      for(int j = 1; j < i; j++) {
			    	  sql += " OR " + productID[j];
			      }
			      //System.out.println(sql);
			      ResultSet rs = stmt.executeQuery(sql);
			      while ( rs.next() ) {
			    	  price1 = rs.getDouble("SUM(DISTINCT p_cost)");
			    	  
			    	  System.out.println("The total cost of your order will be $" + String.format("%.2f", (price1 - (price1 * discount))));
				  }
			      rs.close();
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
			
			String orderStatus;
			System.out.println("Would you like to pick up your order or have it delivered?");
			System.out.println("[1]Delivery\t[2]Pick-up");
			option = scan.next();
			while(!option.equals("1") && !option.equals("2")) {
				System.out.println("Invalid input, please enter a number corresponding to your choice: ");
				option = scan.next();
			}
			if(option.equals("1")) {
				orderStatus = "delivery";
			}
			else
				orderStatus = "pick-up";
			
			String paymentMethod;
			String cardName;
			String cardNum;
			String bank;
			if(orderStatus.equals("pick-up")) {
				System.out.println("Would you like to pay with card or cash?\n[1]Card\t[2]Cash");
				option = scan.next();
				while(!option.equals("1") && !option.equals("2")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice: ");
					option = scan.next();
				}
				if(option.equals("1"))
					paymentMethod = "card";
				else {
					paymentMethod = "cash";
					cardNum = "0";
					bank = "NULL";
				}
			}
			else {
				paymentMethod = "card";
			}
			
			if(paymentMethod.equals("card")) {
				System.out.println("Please enter the name on your card (first and last):");
				scan.nextLine();
				cardName = scan.nextLine();
				System.out.println("Please enter your card number:");
				cardNum = scan.next();
				System.out.println("Please enter your bank's name:");
				scan.nextLine();
				bank = scan.nextLine();
				
				//TO DO: Enter the payment information and the order in the database
				try {
				      Class.forName("org.sqlite.JDBC");
				      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
				      c.setAutoCommit(false);
				      
				      String custZip = " ";
				      String custCityID = " ";
				      String custStreet = " ";

				      stmt = c.createStatement();
				      String sql = "SELECT cust_street, cust_cityID, cust_zip FROM Customer WHERE cust_ID = " + custID; 
				      ResultSet rs = stmt.executeQuery(sql);
				      while ( rs.next() ) {
				    	   custStreet = rs.getString("cust_street");
				    	   custCityID = rs.getString("cust_cityID");
				    	   custZip = rs.getString("cust_zip");
				    	   
					  }
				      
				      int random1 = 0;
				      int random2;
				      sql = "INSERT INTO Orders VALUES(" + random1 + ", " + custID + ", '" + orderStatus + "', '" + name + "', '" + custStreet + "', " + custCityID + ", " + custZip + ", " + price1 + ", " + distID[0] + ");";
				      /*for(int j = 0; j < i; j++) {
				    	  random1 = (int)(Math.random()*(1000)+1);
				    	  sql = "INSERT INTO Orders VALUES(" + random1 + ", " + custID + ", '" + orderStatus + "', '" + name + "', '" + custStreet + "', " + custCityID + ", " + custZip + ", " + price1 + ", " + distID[j] + ");";
				    	  sql = "INSERT INTO Orders VALUES(" + random1 + ", " + custID + ", '" + orderStatus + "', '" + name + "', '" + custStreet + "', " + custCityID + ", " + custZip + ", " + price1 + ", " + distID[j] + ");";
				    	  stmt.executeUpdate(sql);
				      }*/
				      
				      random2 = (int)(Math.random()*(1000)+1);
				      sql = "INSERT INTO Payment VALUES(" + random2 + ", " + random1 + ", '" + paymentMethod + "', " + price1 + ", '" + name + "', " + cardNum + ", '" + bank + "', 2020-03-12, 23);";
				      stmt.executeUpdate(sql);
				      rs.close();
				      stmt.close();
					  c.close();
				   } catch ( Exception e ) {
				      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
				      System.exit(0);
				   }
			}
			
			//The purchase has been made and the order has been entered, so just exit the program
			System.out.println("Your order has been processed, thank you for your purchase!");
			System.exit(0);
			
			
			
		}
		else if(option.equals("2")) {
			//The customer wants to change their profile
			boolean correctInput = false;
			while(!correctInput) {
				System.out.println("Enter your first and last names: ");
				scan.nextLine();
				name = scan.nextLine();
				System.out.println("Enter your street name/house number: ");
				String street = scan.nextLine();
				System.out.println("Enter your zip code: ");
				String zip = scan.next();
				System.out.println("Enter your city name: ");
				String city = scan.next();
				System.out.println("Enter your phone number: ");
				String phoneNumber = scan.next();
				System.out.println("Enter your age: ");
				String age = scan.next();
				int random = (int)(Math.random()*(1000)+1);
				
				System.out.println();
				System.out.println("Does this information look correct?");
				System.out.println("Name: " + name);
				System.out.println("Address: " + street + " " + zip + " " + city + " CA");
				System.out.println("City: " + city);
				System.out.println("Phone number: " + phoneNumber);
				System.out.println("Age: " + age);
				System.out.println("[1]Yes\t[2]No");
				option = scan.next();
				
				
				while(!option.equals("1") && !option.equals("2") && !option.equalsIgnoreCase("q")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				
				//If the data is correct, add this user to the system
				if(option.equals("1")) {
					//TO DO: add this user to the system!
					try {
					      Class.forName("org.sqlite.JDBC");
					      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
					      c.setAutoCommit(false);
					      int cityID = 0;

					      stmt = c.createStatement();
					      String sql = "SELECT city_ID FROM city WHERE city_name = '" + city + "'";
					      ResultSet rs1 = stmt.executeQuery(sql);
					      while ( rs1.next() ) {
					    	  cityID = rs1.getInt("city_ID");
					      }
					      rs1.close();
					      
					      sql = "UPDATE Customer SET cust_name = '" + name + "', cust_ street = '"+ street + "', cust_cityID = "+ cityID + ", cust_zip = " + zip + ", cust_contact = " + phoneNumber + ", cust_age = " + age + " WHERE cust_ID = " + custID + ";";
					      stmt.executeUpdate(sql);
					      //System.out.println(sql);
					      stmt.close();
						  c.close();
					   } catch ( Exception e ) {
					      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
					      System.exit(0);
					   }
					
					System.out.println("Your information has been updated successfully!");
				}
				else if(option.equalsIgnoreCase("q")) {
					System.out.println("Thank you, goodbye!");
					System.exit(0);
				}
				
				//Option = 2, so the values are not correct
				else {
					//Goes back to the beginning of the loop so the user can re-enter the right values.
					System.out.println("Please re-enter the correct data.");
				}
			}
		}
		
		//The customer has typed 'q' and wants to quit
		else {
			System.out.println("Thank you, goodbye!");
			System.exit(0);
		}
	}
	
	//This method is for running all the distributor use cases!
	static void runDistributor() {
		Connection c = null;
		Statement stmt = null;
		Scanner scan = new Scanner(System.in);
		String option;
		int distID = 0;
		String distName = " ";
		
		//Gets the customer's name
		boolean foundName = false;
		System.out.println("Please enter your ID number: ");
		distID = scan.nextInt();
		System.out.println("Checking the system....");
		
		//This will keep looping until the user either quits, decides to make an new profile, or enters a valid name
		while(!foundName) {
			//TO DO: Check the database for the customer name
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);

			      stmt = c.createStatement();
			      String sql = "SELECT dist_ID, dist_name FROM Distributor WHERE dist_ID = " + distID + ";";
			      //System.out.println(sql);
			      ResultSet rs = stmt.executeQuery(sql);
			      while ( rs.next() ) {
			    	  distID = rs.getInt("dist_ID");
			    	  distName = rs.getString("dist_name");
				      
			    	  foundName = true;
			      }
			      rs.close();
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
			
			if(foundName) {
				break;
			}
			else {
				System.out.println("This ID number is not part of the system. Please re-enter the correct ID.");
			}
		}
		System.out.println("Hello " + distName + ", what would you like to do?");
		System.out.println("[1]Look at orders\t[2]Update profile\t[3]Add a product\t[4]Delete a product");
		option = scan.next();
		while(!option.equals("1") && !option.equals("2") && !option.equals("3") && !option.equals("4")) {
			System.out.println("Invalid input, please enter a number corresponding to your choice: ");
			option = scan.next();
		}
		
		//They want to look at their orders
		if(option.equals("1")) {
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);

			      stmt = c.createStatement();
			      String sql = "SELECT o_orderID, o_orderstatus, o_name, o_to_street, o_cityID, o_to_zip, o_totalPrice FROM Orders WHERE o_dist_ID = " + distID + "";
			      //System.out.println(sql);
			      ResultSet rs = stmt.executeQuery(sql);
			      while ( rs.next() ) {
			    	  int orderID = rs.getInt("o_orderID");
			    	  String orderStatus = rs.getString("o_orderstatus");
			    	  String name4 = rs.getString("o_name");
			    	  String street = rs.getString("o_to_street");
			    	  int cityID = rs.getInt("o_cityID");
			    	  int zip = rs.getInt("o_to_zip");
			    	  double price = rs.getDouble("o_totalPrice");
			    	  
			    	  System.out.println("[" + orderID + "] Customer name: " + name4);
			    	  System.out.println("Order address: " + street + " " + zip + "\nCity ID: " + cityID + "\nAmount paid: " + price);
			    	  System.out.println("-------------------------------------------------------------------------------------");
				      
			    	  foundName = true;
			      }
			      rs.close();
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
			System.out.println("Do you want to delete a fulfilled order?");
			System.out.println("[1]Yes\t[2]No");
			option = scan.next();
		}
		//They want to update their profile
		else if(option.equals("2")) {
			//The customer wants to change their profile
			boolean correctInput = false;
			while(!correctInput) {
				System.out.println("Enter distributor name: ");
				scan.nextLine();
				distName = scan.nextLine();
				System.out.println("Enter your street name/address number: ");
				String street = scan.nextLine();
				System.out.println("Enter your zip code: ");
				String zip = scan.next();
				System.out.println("Enter your city name: ");
				String city = scan.next();
				System.out.println("Enter your phone number: ");
				String phoneNumber = scan.next();
				
				System.out.println();
				System.out.println("Does this information look correct?");
				System.out.println("Name: " + distName);
				System.out.println("Address: " + street + " " + zip + " " + city + " CA");
				System.out.println("City: " + city);
				System.out.println("Phone number: " + phoneNumber);
				System.out.println("[1]Yes\t[2]No");
				option = scan.next();
				
				
				while(!option.equals("1") && !option.equals("2") && !option.equalsIgnoreCase("q")) {
					System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
					option = scan.next();
				}
				
				//If the data is correct, update this distributor's profile
				if(option.equals("1")) {
					//TO DO: add this user to the system!
					try {
					      Class.forName("org.sqlite.JDBC");
					      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
					      c.setAutoCommit(false);
					      int cityID = 0;

					      stmt = c.createStatement();
					      String sql = "SELECT city_ID FROM city WHERE city_name = '" + city + "'";
					      ResultSet rs1 = stmt.executeQuery(sql);
					      while ( rs1.next() ) {
					    	  cityID = rs1.getInt("city_ID");
					      }
					      rs1.close();
					      
					      sql = "UPDATE Customer SET dist_name = '" + distName + "', dist_street = '"+ street + "', dist_cityID = "+ cityID + ", dist_zip = " + zip + ", dist_contact = " + phoneNumber + ", cust_age = " + " WHERE dist_ID = " + distID + ";";
					      stmt.executeUpdate(sql);
					      //System.out.println(sql);
					      stmt.close();
						  c.close();
					   } catch ( Exception e ) {
					      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
					      System.exit(0);
					   }
					
					System.out.println("Your information has been updated successfully!");
				}
				else if(option.equalsIgnoreCase("q")) {
					System.out.println("Thank you, goodbye!");
					System.exit(0);
				}
				
				//Option = 2, so the values are not correct
				else {
					//Goes back to the beginning of the loop so the user can re-enter the right values.
					System.out.println("Please re-enter the correct data.");
				}
			}
		}
		//They want to add a product
		else if(option.equals("3")) {
			System.out.println("Enter the name: ");
			scan.nextLine();
			String prodName = scan.nextLine();
			System.out.println("Enter the scale: ");
			double scale = scan.nextDouble();
			System.out.println("Enter the type: ");
			String type = scan.next();
			System.out.println("Enter the cost: ");
			double cost = scan.nextDouble();
			System.out.println("Enter the THC: ");
			double THC = scan.nextDouble();
			System.out.println("Enter the CBD: ");
			double CBD = scan.nextDouble();
			System.out.println("Enter the strain: ");
			String strain = scan.next();
			System.out.println("Enter the quantity: ");
			int quantity = scan.nextInt();
			System.out.println("Enter the packed by date in format YYYY-MM-DD: ");
			scan.nextLine();
			String packedDate = scan.nextLine();
			System.out.println("Enter the expiration date in format YYYY-MM-DD: ");
			scan.nextLine();
			String expiration = scan.nextLine();
			System.out.println("Enter a short explanation of the effects of this product: ");
			scan.nextLine();
			String effects = scan.nextLine();
			int random = (int)(Math.random()*(1000)+1);
			
			
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);
			      int cityID = 0;

			      stmt = c.createStatement();
			      String sql = "INSERT INTO Product VALUES(" + random + ", '" + prodName + "', "+ scale + ", '"+ type + "', " + distID + ", '" + packedDate + "', '" + expiration + "', " + cost + ", " + THC + ", " + CBD + ", '" + effects + "','" + strain + "', " + quantity + ");";
			      stmt.executeUpdate(sql);
			      //System.out.println(sql);
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
		}
		//They want to delete a product
		else if(option.equals("4")) {
			System.out.println("Enter the ID number of the product you want to delete: ");
			int deleteID = scan.nextInt();
			try {
			      Class.forName("org.sqlite.JDBC");
			      c = DriverManager.getConnection("jdbc:sqlite:/home/annemarie/Desktop/CSE111/MMM");
			      c.setAutoCommit(false);

			      stmt = c.createStatement();
			      String sql = "DELETE FROM Products WHERE p_ID = " + deleteID;
			      stmt.executeUpdate(sql);
			      //System.out.println(sql);
			      stmt.close();
				  c.close();
			   } catch ( Exception e ) {
			      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
			      System.exit(0);
			   }
			
		}
		else {
			System.out.println("Thank you, goodbye!");
			System.exit(0);
		}
		
		
	}
	
	public static void main(String[]args) {
		Scanner scan = new Scanner(System.in);
		//boolean running = true;
		String option;
		System.out.println("Welcome to the medical marijuana store!");
		Connection c = null;
		Statement stmt = null;
		
		while(true) {
			System.out.println("Are you a customer or a distributor? Choose an option or type q to quit: ");
			System.out.println("[1]Customer\t[2]Distributor");
			option = scan.next();
			System.out.println(option);
			while(!(option.equals("1")) && !(option.equals("2")) && !(option.equalsIgnoreCase("q"))) {
				System.out.println("Invalid input, please enter a number corresponding to your choice (or type q to quit): ");
				option = scan.next();
			}
			System.out.println();
			
			if(option.equals("1")) {
				runCustomer();
			}
			else if(option.equals("2")){
				runDistributor();
			}
			else {
				System.out.println("Thank you, goodbye!");
				System.exit(0);
			}
			break;
		}
	}
}
