public class NSConnectionMgr2 {
	static private NSConnectionMgr instance;	//连接池管理类的唯一实例
	
	static private int clients;//客户数量
	
	private ArrayList drivers = new ArrayList();	//容器，存放数据库驱动程序
	
	private HashMap pools = new HashMap();	//以name/value的形式存取连接池对象的名字及连接池对象
	
	public static synchronized NSConnectionMgr getInstance();	//如果唯一的实例instance已经创建，直接返回这个实例;否则，调用私有构造函数，创建连接池管理类的唯一实例
	
	private NSConnectionMgr();	//私有构造函数,在其中调用初始化函数init()
	
	public void freeConnection(String name, Connection con);	//释放一个连接，name是一个连接池对象的名字
	
	public NSConnection getConnection(String name);	//从名字为name的连接池对象中得到一个连接
	
	public NSConnection getConnection(String name,long time);	//从名字为name的连接池对象中取得一个连接，time是等待时间
	
	public synchronized void release();	//释放所有资源
	
	private void createPools(Properties props);	//根据属性文件提供的信息，创建一个或多个连接池
	
	private void init();	//初始化连接池管理类的唯一实例，由私有构造函数调用
	
	private void loadDrivers(Properties props);	//装载数据库驱动程序
}
