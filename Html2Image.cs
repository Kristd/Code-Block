
/* 
 * RemoveTable: Use web browser component to convert a html table to image  
 */ 
 
public static string RemoveTable(string html)
{
    int beginIndex = 0;
    int endIndex = 0;
    int tableTag = 0;
    string strTable = string.Empty;
    List<TableObj> tableList = new List<TableObj>();

    //bonerce: group expression is a feathure under .Net only
    //<div id="b">[^<>]*(((?'Open'<div[^>]*>)[^<>]*)+((?'-Open'</div>)[^<>]*)+)*(?(Open)(?!))</div>

    //regular expression: match all the html table begin tag "<table>" and the end tag "</table>"
    Regex regex = new Regex(@"(?is)<table|</table", RegexOptions.Singleline);       
    MatchCollection matchColl = regex.Matches(html);

    foreach (Match match in matchColl)
    {
        //when it met a "<table>", then just put it in the stack 
        if (match.Value.ToLower() == "<table")
        {
            tableTag++;

            if (beginIndex == 0)
            {
                beginIndex = match.Index;
            }
        }

        //when it met a "</table>", then just delete a "<table>" in the stack
        if (match.Value.ToLower() == "</table")
        {
            tableTag--;
        }

        //found the last correct "</table>" and then cut this html code block
        if(tableTag == 0)
        {
            TableObj tbObj = new TableObj();
            endIndex = match.Index - beginIndex + 8;
            strTable = html.Substring(beginIndex, endIndex);
            
            tbObj.m_stream = strTable;
            tbObj.m_beginIndex = beginIndex;
            tbObj.m_endIndex = endIndex;
            tableList.Add(tbObj);

            beginIndex = 0;
        }
    }

    //convert the html to image
    tableList = HtmlToImg.GetHtmlToImg(tableList);

    //replace the table in html with img
    foreach (TableObj tbObj in tableList)
    {
        html = html.Replace(tbObj.m_stream, tbObj.m_imageTag);
    }
    
    return html;
}


public class TableObj
{
    public int m_beginIndex;
    public int m_endIndex;
    public string m_stream;
    public string m_imageTag;

    public TableObj()
    {
        m_beginIndex = 0;
        m_endIndex = 0;
        m_stream = string.Empty;
        m_imageTag = string.Empty;
    }
}


class HtmlToImg
{
    Bitmap m_Bitmap;
    List<TableObj> m_tableList;
    int m_BrowserWidth, m_BrowserHeight, m_ThumbnailWidth, m_ThumbnailHeight;

    public HtmlToImg(List<TableObj> tableList)
    {
        m_tableList = tableList;
        m_BrowserHeight = 500;      //browser height
        m_BrowserWidth = 500;       //browser width
        m_ThumbnailWidth = 500;     //image width
        m_ThumbnailHeight = 500;    //image height
    }

    public static List<TableObj> GetHtmlToImg(List<TableObj> tableList)
    {
        HtmlToImg thumbnailGenerator = new HtmlToImg(tableList);
        return thumbnailGenerator.GenerateHtmlToImage();
    }

    private List<TableObj> GenerateHtmlToImage()
    {
        WebBrowser m_WebBrowser = new WebBrowser();
        m_WebBrowser.ScrollBarsEnabled = false;

        foreach(TableObj tbObj in m_tableList)
        {
            Encoding.GetEncoding("UTF-8").GetString(Encoding.GetEncoding("UTF-8").GetBytes(tbObj.m_stream));

            m_WebBrowser.DocumentText = tbObj.m_stream;
            m_WebBrowser.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(WebBrowser_DocumentCompleted);        //use browser event function

            while (m_WebBrowser.ReadyState != WebBrowserReadyState.Complete)
            {
                Application.DoEvents();
            }

            tbObj.m_imageTag = SaveImage();         //save the image
        }

        m_WebBrowser.Dispose();
        return m_tableList;
    }

    private void WebBrowser_DocumentCompleted(object sender, WebBrowserDocumentCompletedEventArgs e)
    {
        WebBrowser m_WebBrowser = (WebBrowser)sender;
        m_WebBrowser.ClientSize = new Size(this.m_BrowserWidth, this.m_BrowserHeight);
        m_WebBrowser.ScrollBarsEnabled = false;
        m_Bitmap = new Bitmap(m_WebBrowser.Bounds.Width, m_WebBrowser.Bounds.Height);
        m_WebBrowser.BringToFront();
        m_WebBrowser.DrawToBitmap(m_Bitmap, m_WebBrowser.Bounds);
        m_Bitmap = (Bitmap)m_Bitmap.GetThumbnailImage(m_ThumbnailWidth, m_ThumbnailHeight, null, IntPtr.Zero);
    }

    private string SaveImage()
    {
        string sysfold = Application.StartupPath;
        MemoryStream stream = new MemoryStream();
        m_Bitmap.Save(stream, System.Drawing.Imaging.ImageFormat.Gif);
        byte[] buff = stream.ToArray();

        int count = 0;
        DateTime dt = DateTime.Now;
        string fileName = dt.Ticks.ToString() + count++;        //create the filename according to the time ticket

        string copydirectory = sysfold + HtmlUtil.uploadfile;
        string savePath = copydirectory + fileName + ".gif";

        FileStream fs = new FileStream(savePath, FileMode.Create);
        stream.WriteTo(fs);
        stream.Close();
        fs.Close();

        return ConvertToHtmlImage(savePath);
    }

    private string ConvertToHtmlImage(string savePath)
    {
        savePath = @"file:///" + savePath;
        string strHtmlImage = "<img src=\"" + savePath + "\">";
        return strHtmlImage;
    }
}




