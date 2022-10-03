package mydb;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class test3 {

	public static void main(String[] args) {
		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null; 
			con = DBUtil.getConnection();
		String name= "";

		String sql = "select * from tbl_users where user_email = ? and password = ?";
		try {
				pstmt = con.prepareStatement(sql);
				pstmt.setString(1, "sdaf@naver.com");
				pstmt.setString(2, "password");
				rs = pstmt.executeQuery();				
		    while(rs.next()){
			name= (String) rs.getString("user_name");
		    }	           
		}catch(Exception e){
			
		}finally{
				// TODO Auto-generated catch block
			DBUtil.close(rs, pstmt, con);
		}System.out.println(name);
	}
}
