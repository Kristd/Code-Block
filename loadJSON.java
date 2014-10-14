public static String formatJSONString(String str) {
		if (str != null && !str.equals("")) {
			Pattern p = Pattern.compile("\\s*|\t|\r|\n");
			Matcher m = p.matcher(str);
			return m.replaceAll("");
		} 
		else {
			return "";
		}
	}
	
	public static Object loadJSON(String fileName) {
        File file = new File(fileName);
        BufferedReader reader = null;
        String fileBuff = new String("");
        String temp = new String("");
        
        try {
            reader = new BufferedReader(new FileReader(file));
            
            while ((temp = reader.readLine()) != null) {
                fileBuff += temp;
            }
            
            fileBuff = fileBuff.trim();
            
            if(fileBuff.charAt(0) == '[') {
            	return (new JSONArray(fileBuff));
            }
            else if(fileBuff.charAt(0) == '{') {
            	return (new JSONObject(fileBuff));
            }
            else {
            	// TODO add error log
            	return null;
            }
        } 
        catch (IOException e) {
            e.printStackTrace();
            return null;
        } 
        finally {
            if (reader != null) {
                try {
                    reader.close();
                } 
                catch (IOException e) {
                	e.printStackTrace();
                }
            }
        }
    }
