package mydb;

import java.sql.Connection;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class test3 {

	public static void main(String[] args) {

		Connection con = null;       //연결
		PreparedStatement pstmt = null; //명령
		ResultSet rs = null; 
		con = DBUtil.getConnection();
		JSONArray jsonArray = new JSONArray();
		String sql = "select temperature from tbl_status where user=? order by time DESC limit 1";
		try {
			pstmt = con.prepareStatement(sql);			
			pstmt.setString(1, "jiseong");
			rs = pstmt.executeQuery();
			
			while (rs.next()) {

				JSONObject jsonObject = new JSONObject(); //Map컬렉션

				jsonObject.put("temp",rs.getString("temperature"));

				jsonArray.add(jsonObject);

				}  
		          
	    }catch(Exception e){
	    	
	    }
	    finally{
				// TODO Auto-generated catch block
		DBUtil.close(rs, pstmt, con);
			}System.out.println(jsonArray);
			/*
			 * JSONObject jsonob = new JSONObject(); JSONArray jsonarr = new JSONArray();
			 * 
			 * JSONObject data = new JSONObject(); data.put("temperature", tempList);
			 * System.out.println(data);
			 */
	}

}
