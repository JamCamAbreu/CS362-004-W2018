import junit.framework.TestCase;

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   /***********************************************
    *              MANUAL TESTING
    **********************************************/
   
   // ---------- JAMES ABREU MANUAL TEST ----------
   public void testManualTest_Cam() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // First test a few well known sites:
	   assertTrue(urlVal.isValid("http://www.google.com") == true);
	   assertTrue(urlVal.isValid("http://www.amazon.com") == true);
	   assertTrue(urlVal.isValid("http://www.youtube.com") == true);  
	   
	   // add path:
	   assertTrue(urlVal.isValid("http://www.google.com/") == true);
	   assertTrue(urlVal.isValid("http://www.amazon.com/") == true);
	   assertTrue(urlVal.isValid("http://www.youtube.com/") == true);
   } // end manual test
   
   
   
   
   
   // ---------- CHRIS BUGSCH MANUAL TEST ----------
   public void testManualTest_Chris() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	 
	   if (urlVal.isValid("http://www.google.com")) {
		    //     System.out.println("url is valid");
		       } else {
		          System.out.println("url is invalid");
		       }
   } // end manual test
    
   
   
   
   
   // ---------- ZACHARY STARK MANUAL TESTS ----------
   public void oracle(String val, Boolean boolVal) {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   Boolean result = urlVal.isValid(val);
	   if (result == boolVal) {
		   System.out.print(val + " ");
		   System.out.print("GOOD, is: " + result + " should be: " + boolVal + "\n");
	   }
	   
	   else {
		   System.out.print(val + " ");
		   System.out.print("BAD, is: " + result + " should be: " + boolVal + "\n");
	   }
   }
   
   public void testManualTest() {
	   //You can use this function to implement your manual testing	   
	   oracle("http://www.google.com", true);
	   oracle("http://www.google.com/", true);
      
	   //trying invalid ip address style url
	   oracle("http://256.267.256.245/something.htm", false);
	   oracle("http://1.1.1.1.1", false);
	   
	   //cause isValid to crash java.lang.IllegalArgumentException thrown
	   //oracle("ftp://2.1.13.134.12/something.htm", false);
    
	   //try different protocols
	   oracle("http://www.google.com/", true);
	   
	   //cause isValid to crash java.lang.IllegalArgumentException thrown
	   oracle("ftp://www.google.com/", true);
	   //oracle("https://www.google.com/", true);
	   //oracle("mailto://www.google.com/", true);
	   //oracle("file://www.google.com/", true);
	   //oracle("data://www.google.com/", true);
   }
   
   
   
   
   
   
   
   
   
   
   /***********************************************
    *             PARTITION TESTING
    **********************************************/
   
   // Test the SCHEME
   public void testSchemePartition() {
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	 
	System.out.printf("\nTesting scheme partition:\n");
	
	System.out.printf("\tTesting 'http'... ");
	 if (urlVal.isValid("http://www.google.com")) { System.out.printf("passed");}
	 else {System.out.printf("failed");} 
   }
   
   // Test the PATH
   public void testPathPartition() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 
		System.out.printf("\nTesting path partition:\n");
		
		System.out.printf("\tTesting '/home'... ");
		 if (urlVal.isValid("http://www.google.com/home")) { System.out.printf("passed");}
		 else {System.out.printf("failed");} 
			
		System.out.printf("\n\tTesting '<home>'... ");
		if(!urlVal.isValid("http://www.google.com")) { System.out.printf("passed");}
		else {System.out.printf("failed");} 
   }
   
   // Test the AUTHORITY
   public void testAuthorityPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 
		System.out.printf("\nTesting authority partition:\n");
		
		System.out.printf("\tTesting '1.1.1.1'... ");
		 if (urlVal.isValid("http://1.1.1.1")) { System.out.printf("passed");}
		 else {System.out.printf("failed");} 
			
		System.out.printf("\n\tTesting '1.1.1.1.1'... ");
		if(!urlVal.isValid("http://1.1.1.1.1")) { System.out.printf("passed");}
		else {System.out.printf("failed");} 

   }
   
   // Test the QUERY
   public void testQueryPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		 
		System.out.printf("\nTesting query partition:\n");
		
		System.out.printf("\tTesting '?action=view'... ");
		 if (urlVal.isValid("http://www.google.com/?action=view'... "))
       System.out.printf("passed");
		 else {System.out.printf("failed");} 
			
		System.out.printf("\n\tTesting '?action<view ");
		if(!urlVal.isValid("http://www.google.com"))
      System.out.printf("passed");
		else {System.out.printf("failed");} 

   }
  

   
   
   
   
   
   
   
   
   
   
   
   
   /***********************************************
    *        PROGRAMMING BASED TESTING
    **********************************************/
   
   public void testIsValid() {

	   // NOTE: Check files in package to see the 'pieces' of the URL: 
	   // schemes.java, commonDomains.java, validPorts.java, validPaths.java
	   // This test is an exhaustive test of all the possible combinations of those pieces.
	   
	   // Initialize a new UrlValidator:
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String scheme;
	   String domain;
	   String port;
	   String path;
	   String fullString;
	   boolean ret;
	   
	   // loop through each component list and build the string to be tested:
		 // HERE IS ALL of the schemes:
	   for (int sch = 0; sch < (schemes.allSchemes.size()); sch++) {
		   scheme = schemes.allSchemes.get(sch);
	   
		   // HERE IS ALL of the domains:
		   for (int dom = 0; dom < (commonDomains.domains.size()); dom++) {
			   domain = commonDomains.domains.get(dom);
		   
			   // HERE IS ALL of the valid ports:
			   for (int por = 0; por < (validPorts.ports.size()); por++) {
				   port = validPorts.ports.get(por);
			   
				   // HERE IS ALL of the valid paths:
				   for (int pat = 0; pat < (validPaths.paths.size()); pat++) {
					   path = validPaths.paths.get(pat);
					   
             // Combine the components into one string:
					   fullString = scheme + domain + port + path;
					   
					   // TEST HERE!
					   ret = urlVal.isValid(fullString);
					   
					   // IF NOT TRUE, output the false URL:
					   if (ret != true) {
						   // let's see the full path!
						   System.out.println(fullString);
					   }
						   
				   } // end for paths
			   } // end for ports
		   } // end for domains
	   } // end for schemes
   } // end testIsValid
   

}
