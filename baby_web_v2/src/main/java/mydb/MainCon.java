package mydb;
import java.sql.*;
import java.util.Date;
import java.util.TimeZone;

public class MainCon {
	public MainCon() {}
	public String dailysnow(String Site){
		String device = "";
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null;         //결과
		String daily ="";
		    con = DBUtil.getConnection();
		    String sql = "select DailySnow from tbl_snow where Site = ? order by Time DESC limit 1 ";
		    try {
					pstmt = con.prepareStatement(sql);			
					pstmt.setString(1, device);
					rs = pstmt.executeQuery();
		    if(rs.next()){
			daily = rs.getString("DailySnow");  
		    }           
		    }catch(Exception e){
			return "1.0";
		    }finally{
					// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
				}
		    return daily;
	}

	public int getCnt(String key) {
		int i = 0;
		int cnt = 0;
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null; 
			con = DBUtil.getConnection();
		String sql = "select * from sensor_record where serial_num like ? or site_num like ? or fw_ver like ? or ir_data like ? or"+
			" angle like ? or logger_type like ? or business like ? or address like ? or coment like ? or lastediter like ? order by serial_num asc";	
		try {
				pstmt = con.prepareStatement(sql);
				for(int a=1; a<11; a++){
					pstmt.setString(a, "%"+key+"%");
				}
				rs = pstmt.executeQuery();				
		    while(rs.next()){
			i++; 
		    }	           
		}catch(Exception e){
			return 0;
		}finally{
				// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
			}
			if(i != 0){
			cnt = i;
		}
			return cnt;
	}

	public int insertDB(String serial, String date, String site, String fw, String ir, String angle, String logger, String business, String add, String coment, String editer, String lastday) throws SQLException{
		String sql = "insert into sensor_record values(?,?,?,?,?,?,?,?,?,?,?,?)";
		Connection con = null;
		 PreparedStatement pstmt = null;
		 int result = 0;
		try{
		con = DBUtil.getConnection();
		
		pstmt = con.prepareStatement(sql);
		pstmt.setString(1,serial);
		pstmt.setString(2,date);
		pstmt.setString(3,site);
		pstmt.setString(4,fw);
		pstmt.setString(5,ir);
		pstmt.setString(6,angle);
		pstmt.setString(7,logger);
		pstmt.setString(8,business);
		pstmt.setString(9,add);
		pstmt.setString(10,coment.replace(',', '.'));
		pstmt.setString(11,editer);
		pstmt.setString(12,lastday);
		
		result = pstmt.executeUpdate();
		}finally{
			DBUtil.close(pstmt,con);
		}
		 return result;
	}

	public void updateSensor(String serial, String date, String site, String fw, String ir, String angle, String logger, String business, String add, String coment, String editer,String day) throws SQLException{
		String sql = "update sensor_record set date = ?, site_num = ?, fw_ver = ?, ir_data = ?, angle = ?, logger_type = ?, business = ?, address = ?, coment = ?,lastediter = ?, lastday = ? where serial_num = ?";
		Connection con = null;
		 PreparedStatement pstmt = null; 
		 
		 try{
				con = DBUtil.getConnection();
				pstmt = con.prepareStatement(sql);
				pstmt.setString(1, date);
				pstmt.setString(2, site);
				pstmt.setString(3, fw);
				pstmt.setString(4, ir);
				pstmt.setString(5, angle);
				pstmt.setString(6, logger);
				pstmt.setString(7, business);
				pstmt.setString(8, add);
				pstmt.setString(9, coment.replace(',', '.'));		
				pstmt.setString(10, editer);
				pstmt.setString(11, day);
				pstmt.setString(12, serial);
				pstmt.executeUpdate();
		 }finally{
				DBUtil.close(pstmt,con);
		 
		 }
	}

	public void deleteSensor(String key) throws SQLException{
		String sql = "delete from sensor_record where serial_num = ?";
		Connection con = null;
		 PreparedStatement pstmt = null; 
		 try{
				con = DBUtil.getConnection();
				pstmt = con.prepareStatement(sql);
				pstmt.setString(1, key.trim());
				pstmt.executeUpdate();
		 }finally{
				DBUtil.close(pstmt,con);
		 
			}
	}

	public String doLogin(String id, String pwd){
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null; 
			con = DBUtil.getConnection();
		String name= "";

		String sql = "select * from member where id = ? and pwd = ?";
		try {
				pstmt = con.prepareStatement(sql);
				pstmt.setString(1, id.trim());
				pstmt.setString(2, pwd.trim());
				rs = pstmt.executeQuery();				
		    while(rs.next()){
			name= (String) rs.getString("name");
		    }	           
		}catch(Exception e){
			return " ";
		}finally{
				// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
			}
		return name;
	}
	
	public float getTemp() {
		String user = "ji";
		float temp = 1;
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null;         //결과
		con = DBUtil.getConnection();
		String sql = "select temperature from tbl_status where user=? order by time DESC limit 1";

		try {
				pstmt = con.prepareStatement(sql);			
				pstmt.setString(1, user);
				rs = pstmt.executeQuery();
				if(rs.next()){
					temp = rs.getFloat("temperature");  
				}           
		    }catch(Exception e){
		    	
		    }
		    finally{
					// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
				}
		return temp;
	}
	public int getBpm() {
		String user = "ji";
		int bpm = 0;
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null;         //결과
		con = DBUtil.getConnection();
		String sql = "select airbpm from tbl_status where user=? order by time DESC limit 1";

		try {
				pstmt = con.prepareStatement(sql);			
				pstmt.setString(1, user);
				rs = pstmt.executeQuery();
				if(rs.next()){
					bpm = rs.getInt("airbpm");  
				}           
		    }catch(Exception e){
		    	
		    }
		    finally{
					// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
				}
		return bpm;
	}
	public String getState() {
		String user = "ji";
		String state = new String();
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null;         //결과
		con = DBUtil.getConnection();
		String sql = "select state from tbl_status where user=? order by time DESC limit 1";

		try {
				pstmt = con.prepareStatement(sql);			
				pstmt.setString(1, user);
				rs = pstmt.executeQuery();
				if(rs.next()){
					state = rs.getString("state");  
				}           
		    }catch(Exception e){
		    	
		    }
		    finally{
					// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
				}
		return state;
	}
	public int insertUser(String name, String email, String password) throws SQLException{
		String sql = "insert into sensor_record values(?,?,?,?,?,?,?,?,?,?,?,?)";
		Connection con = null;
		 PreparedStatement pstmt = null;
		 int result = 0;
		try{
		con = DBUtil.getConnection();
		
		pstmt = con.prepareStatement(sql);
		pstmt.setString(1,name);
		pstmt.setString(2,email);
		pstmt.setString(3,password);
		
		
		result = pstmt.executeUpdate();
		}finally{
			DBUtil.close(pstmt,con);
		}
		 return result;
	}

}
