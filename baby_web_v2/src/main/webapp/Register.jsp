<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%@ page import="mydb.MainCon" %>
<%@ page import="mydb.DBUtil" %>

<!DOCTYPE html>
<html lang="en">

<head>

    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <meta name="description" content="">
    <meta name="author" content="">

    <title>SB Admin 2 - Register</title>

    <!-- Custom fonts for this template-->
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css">
    <link
        href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i"
        rel="stylesheet">

    <!-- Custom styles for this template-->
    <link href="css/Baby-home.min.css" rel="stylesheet">
<% MainCon mc = new MainCon();

String Pwd="";
String RePwd="";
String name = "";
String email = "";

name = (String)request.getParameter("fist_name") + " " + (String)request.getParameter("last_name"); 
Pwd = (String)request.getParameter("password");
RePwd = (String)request.getParameter("password");
email = (String)request.getParameter("email");

System.out.println(name);
System.out.println(Pwd);
System.out.println(email);

if(email == null){
	email=" ";
}
if(Pwd == null){
	Pwd=" ";
}
if(!name.equals(" ") && !Pwd.equals(" ") && !email.equals(" ")){
	if(mc.insertUser(name, email, Pwd) == 1){
		response.sendRedirect("login.jsp");
	}else{
		%>		
		<script type="text/javascript">
			alert("이미 사용중인 아이디입니다.");
		</script>
	<%
	}
}
%>
</head>
<!-- <script type="text/javascript"> -->
// 	var frm = document.myfrm;
	
// 	frm.action = "UserIsert.jsp"
// 	frm.submit();
<!-- </script> -->
<body class="bg-gradient-primary">

    <div class="container">

        <div class="card o-hidden border-0 shadow-lg my-5">
            <div class="card-body p-0">
                <!-- Nested Row within Card Body -->
                <div class="row">
                    <div class="col-lg-7">
                        <div class="p-5">
                            <div class="text-center">
                                <h1 class="h4 text-gray-900 mb-4">Create an Account!</h1>
                            </div>
                            <form class="user" name ="myfrm">
                                <div class="form-group row">
                                    <div class="col-sm-6 mb-3 mb-sm-0">
                                        <input type="text" class="form-control form-control-user" name = "first_name" id="FirstName"
                                            placeholder="First Name">
                                    </div>
                                    <div class="col-sm-6">
                                        <input type="text" class="form-control form-control-user" name = "last_name" id="LastName"
                                            placeholder="Last Name">
                                    </div>
                                </div>
                                <div class="form-group">
                                    <input type="text" class="form-control form-control-user" name = "email" id="InputEmail"
                                        placeholder="Email Address">
                                </div>
                                <div class="form-group row">
                                    <div class="col-sm-6 mb-3 mb-sm-0">
                                        <input type="password" name = "password" class="form-control form-control-user" 
                                            id="InputPassword" placeholder="Password">
                                    </div>
                                    <div class="col-sm-6">
                                        <input type="password" class="form-control form-control-user" 
                                            id="RepeatPassword" placeholder="Repeat Password">
                                    </div>
                                </div>
                                <input type = "submit" href="login.jsp" class="btn btn-primary btn-user btn-block"  value ="Register Account">
                                    
                                
                                <hr>
                                <a href="index.jsp" class="btn btn-google btn-user btn-block">
                                    <i class="fab fa-google fa-fw"></i> Register with Google
                                </a>
                                <a href="index.jsp" class="btn btn-facebook btn-user btn-block">
                                    <i class="fab fa-facebook-f fa-fw"></i> Register with Facebook
                                </a>
                            </form>
                            <hr>
                            <div class="text-center">
                                <a class="small" href="forgot-password.html">Forgot Password?</a>
                            </div>
                            <div class="text-center">
                                <a class="small" href="login.html">Already have an account? Login!</a>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

    </div>
    

    <!-- Bootstrap core JavaScript-->
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>

    <!-- Core plugin JavaScript-->
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>

    <!-- Custom scripts for all pages-->
    <script src="js/Baby-home.min.js"></script>

</body>

</html>