package extraservices.servlet;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import ota.business.BusinessDistribute;
import ota.business.IGeneralReqProc;
import ota.constant.ConstantChar;
import ota.constant.ConstantKey;
import ota.io.pkgparser.IoParser;
import ota.io.pkgparser.url.BankDPANOperationParser;
import ota.io.pkgparser.url.DiscardDPANFromMobileBankParser;

import BaseLib.Global;

/**
 * @author chenzanbiao
 * 2014.4.18
 * ������bserver���ͨ��
 * Servlet implementation class BServerServlet
 */
public class BServerServlet extends HttpServlet {
	
	public String m_initMsg;
	public boolean m_initValid;
	private static final long serialVersionUID = 1L;

    /**
     * Default constructor. 
     */
    public BServerServlet() {
        // TODO Auto-generated constructor stub
    	super();
    }
    
    
	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

		if(!m_initValid)
        {
			WriteClient(response, m_initMsg);
            return;
        }
    	
    	doPost(request, response);
	}

	
	@Override
	public void destroy() {

		Global.m_lSysLog.WriteLog("System stopped.");
    	Global.destroy();
    	super.destroy();
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String ip = "";
		String client_id = "";
		try {
			if(!m_initValid)
	        {
				WriteClient(response, m_initMsg);
	            return;
	        }
			String checkMsg = "";
            ip = request.getRemoteAddr();
            if(ip == null || ip == "")
            {
            	checkMsg = "ȡ�ͻ���IP��ַʧ��!";
            	Global.m_lUserLog.WriteLog(checkMsg);
            	WriteClient(response, "result=fail&data="+checkMsg);
            	return;
            }
            
            Global.m_lUserLog.WriteLog(ip+"#get request succ"+"#"+Thread.currentThread());
            Map mParas = request.getParameterMap();
            Set keySet = mParas.keySet(); // �õ�key��set
            Iterator iter = keySet.iterator();
            
            //�Ƿ���Ҫ��¼��־��
            while(iter.hasNext())
            {
            	String key = (String)iter.next();
                String[] values = (String[])mParas.get(key);
                Global.m_lUserLog.WriteLog(ip+" Param " +"["+key+"]\t"+Arrays.toString(values));
            }
            
            String strChannal = request.getParameter(ConstantKey.channel);
            String strOpcode = request.getParameter(ConstantKey.opcode);
            
            HashMap<String,Object> requestHashMap = new HashMap<String,Object>();
            
            IoParser parser = null;
            try {
				
				String parserName = Global.urlparser_profile.getString(strChannal , strOpcode);
				
				//����parser�������
				parser = (IoParser)(Class.forName(parserName).newInstance());
				if(null != parser)
					requestHashMap = parser.parse(request);
			} 
            catch (Exception e) 
            {
            	throw new Exception("opcode|channel��Ӧ��parser��Ч"+strOpcode+ " | " + strChannal);
            }

            
            /**
             * businessDistribute��ݲ�ͬ��channal��opcode�ַ����õ���ͬ�Ĵ�����
             * */
       	 	BusinessDistribute businessDistribute = new BusinessDistribute();
       	 	HashMap<String,Object> responseHashMap = businessDistribute.toBusinessClass(requestHashMap);
           
       	 	
       	 	String strResult = "result="+(String)responseHashMap.get(ConstantKey.result)+"&data="+(String)responseHashMap.get(ConstantKey.statusDescription);
       	 	WriteClient(response, strResult);
            
		} catch (Exception e) {
			Global.m_lUserLog.WriteLog(ip +","+client_id+ "doPost():" + e.getMessage());
	        WriteClient(response,"result=fail&data="+e.getMessage());
		}
	}

	public void init(ServletConfig config) throws ServletException   
    {
    	m_initValid = true;
    	
    	super.init(config);
    }
	
	public int WriteClient(HttpServletResponse response,String answer)
    {
		int r=0;
        //   ServletOutputStream out = null; 
        PrintWriter out = null;

        try {
                response.setContentType("Content-type" );
        		response.setContentType("text/html;charset=GBK");
                response.setHeader("Pragma", "No-cache");
                response.setDateHeader("Expires", 0);
                response.setHeader("Cache-Control", "no-cache");    //If html,source can't be obtained
                
                //out=response.getOutputStream();
                out = response.getWriter();
                out.print(answer);
                //m_lUserLog.WriteLog( "do response succ"+"#"+Thread.currentThread());

        }
        catch(Throwable e)
        {
                r=-1;
        }
        finally
        {
            try
            {
                if(out != null)
                {
                    out.close();
                }
            }catch(Exception e)
            {

            }
       }
       return r;
            
    }
}
