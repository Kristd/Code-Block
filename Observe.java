package demo;

import java.util.Observable;
import java.util.Observer;

import com.cmb.Notify.msgob.AtcAck;
import com.cmb.Notify.msgob.MessageAck;
import com.cmb.Notify.msgob.MsgFailInfo;
import com.cmb.Notify.msgob.RcvReport;

public class MySenderObs implements Observer
{

	public void update(Observable arg0, Object arg1)
	{
		if(arg1 instanceof MsgFailInfo)
		{
			// deal send msg fail
			MsgFailInfo fif = (MsgFailInfo) arg1;
			System.out.println("<---Get FailInfo. MsgID: "
					+ fif.msgid.toString() + " From " + arg0.toString()
					+ " Err: ");
			fif.ex.printStackTrace();
		}
		else if(arg1 instanceof MessageAck)
		{
			// deal send msg ack
			MessageAck msgack = (MessageAck) arg1;
			if(msgack.isSendOk())
			{
				System.out.println("<---Msg SendOK. MsgID: "
						+ msgack.getMsgid().toString() + "From "
						+ arg0.toString());
			}
			else
			{
				System.out.println("<---Msg SendFail. MsgID: "
						+ msgack.getMsgid().toString() + " Errcode: "
						+ msgack.getErrcode() + " Errmsg: "
						+ msgack.getErrmsg() + " From " + arg0.toString());
			}
		}
		else if(arg1 instanceof RcvReport)
		{
			// deal receive report
			RcvReport rcvrpt = (RcvReport) arg1;
			System.out.println("<---Get RcvReport. " + rcvrpt.toString()
					+ "From " + arg0.toString());
		}
		else if(arg1 instanceof AtcAck)
		{
			// deal add atc ack
			AtcAck actack = (AtcAck) arg1;
			if(actack.isSendOk())
			{
				System.out.println("<---Atc SendOK. tranID: " + actack.tranid
						+ "From " + arg0.toString());
			}
			else
			{
				System.out.println("<---Atc SendFail. tranID: " + actack.tranid
						+ " Errcode: " + actack.errcode + " Errmsg: "
						+ actack.errmsg + "From " + arg0.toString());
			}
		}
		else if(arg1 instanceof Exception)
		{
			// deal some exception
			Exception e = (Exception) arg1;
			System.out.println("<---From " + arg0.toString()
					+ " Get exception:");
			e.printStackTrace();
		}
		else if(arg1 instanceof String)
		{
			System.out.println(arg1);
		}
	}
}
