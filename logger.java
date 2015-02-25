package com.main;

import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.util.concurrent.atomic.AtomicLong;
import java.io.File;


public class Logger {
	String m_logName;
	byte[] m_mutex = new byte[1];
	SimpleDateFormat m_splDate;
	OutputStream m_fstream;
	OutputStream m_bstream;
	
	public Logger getLogger(String _name) {
		try {
			m_logName =  _name;
			m_fstream = new FileOutputStream(m_logName + "_" + Utility.getCurrentTime("yyyy-MM-dd"), true);
			m_bstream = new BufferedOutputStream(m_fstream);
		} catch (FileNotFoundException ex) {
			// TODO Auto-generated catch block
			ex.printStackTrace();
		} catch (Exception ex) {
			;
		}
		return null;
	}

	public boolean isDebugEnabled() {
		// TODO Auto-generated method stub
		return false;
	}

	public void INFO(String string) {
		writelog();
	}

	public void error(Exception e) {
		// TODO Auto-generated method stub
		
	}

	public void debug(String string) {
		// TODO Auto-generated method stub
		
	}
	
	private synchronized void writeLog(String filePath, String strText) {
		try {
			File file = new File(m_logName + "_" + Utility.getCurrentTime("yyyyMMdd"));
			if(file.exists()) {
				AtomicLong atom = new AtomicLong(0);
			}
			else {
				createLogFile();
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception ex) {
			//TODO add error log;
		}
	}
	
	private synchronized void createLogFile() throws IOException {
		if(m_fstream != null){
			m_fstream.flush();
			m_fstream.close();
		}
		
		if(m_bstream != null) {
			m_bstream.flush();
			m_bstream.close();
		}

		m_fstream = new FileOutputStream(m_logName + "_" + Utility.getCurrentTime("yyyyMMdd"), true);
		m_bstream = new BufferedOutputStream(m_fstream);
	}
}
