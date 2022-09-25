package mydb;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class test3 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
			String user = "";
			float temp = 0;
			Connection con = null;       //연결
			PreparedStatement pstmt = null; //명령
			ResultSet rs = null;         //결과
			con = DBUtil.getConnection();
			String sql = "select temperature from tbl_status where user = ? order by time DESC limit 1";
			try {
					pstmt = con.prepareStatement(sql);			
					pstmt.setString(1, user);
					rs = pstmt.executeQuery();
					if(rs.next()){
				temp = rs.getFloat("temperature");  
			    }           
			    }catch(Exception e){
				
			    }finally{
						// TODO Auto-generated catch block
				DBUtil.close(rs, pstmt, con);
					}System.out.println(temp);
//		String sql = "insert into tbl_users values(?,?,?)";
//		Connection con = null;
//		PreparedStatement pstmt = null;
//		try{
//		con = DBUtil.getConnection();
//		
//		pstmt = con.prepareStatement(sql);
//		pstmt.setString(1,"jiseong");
//		pstmt.setString(2,"sdaf@naver.com");
//		pstmt.setString(3,"password");
//		
//		
//		pstmt.executeUpdate();
//		}finally{
//			DBUtil.close(pstmt,con);
//		}
	}

}
