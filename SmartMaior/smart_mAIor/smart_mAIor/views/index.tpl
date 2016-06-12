<!DOCTYPE HTML>
<!--
	ZeroFour by HTML5 UP
	html5up.net | @ajlkn
	Free for personal and commercial use under the CCA 3.0 license (html5up.net/license)
-->
<html>
	<head>
		<title>Serial Team - Smart citizen</title>
		<meta charset="utf-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1" />
		<link rel="stylesheet" href="css/main.css" />
		
		<!-- <link href="style.css" type="text/css" rel="stylesheet"/> -->
		<link href='http://fonts.googleapis.com/css?family=Source+Sans+Pro' rel='stylesheet' type='text/css'/>
		<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
		<script>

function guid() {
  function s4() {
    return Math.floor((1 + Math.random()) * 0x10000)
      .toString(16)
      .substring(1);
  }
  return s4() + s4() + '-' + s4() + '-' + s4() + '-' +
    s4() + '-' + s4() + s4() + s4();
}
	
	var uid = guid()
	
/******
* Add the received message to Chat window
*******/

function addMessage(user, content) {
  jQuery('<div/>', {
    class: "chatline",
    text: user + ": " + content
  }).appendTo('#chatbox');
  $("#chatbox").attr({
    scrollTop: $("#chatBox").attr("scrollHeight")
  });
}

$(document).ready(function() {
  var request;

  /******
  * Set up the send-message process
  *******/

  $("#chatForm").submit(function(event) {
    var content = $("#content").val()

    if (content != '') {
      console.log("Sending: " + content)
	  addMessage("Zeno", content)
	  $.post('/process', { content:content, uid:uid}, function (data) {
		addMessage("Milan", data.responseMsg)
	  });
      $("#content").val('')
    }

    event.preventDefault();
  });

  // Add a default message
  addMessage("Milan", "Pozdrav od vaseg gradonacelnika Milana! A vi se zovete?")
	
});
	</script>
		
	</head>
	<body class="homepage">
		<div id="page-wrapper">

			<!-- Header -->
				<div id="header-wrapper">
					<div class="container">

						<!-- Header -->
							<header id="header">
								<div class="inner">

									<!-- Logo -->
										<img src="images/komi.png" alt="" /><h1><a href="index.html" id="logo">Serial Team </a></h1>

									<!-- Nav -->
										<nav id="nav">
											<ul>
												<li class="current_page_item"><a href="index.html">Home</a></li>
												<li>
													<a href="#">Smart citizen</a>
													<ul>
														<li><a href="#">About project</a></li>
														<li><a href="#">Future plans</a></li>
													</ul>
												</li>
												<li><a href="help.html">Support</a></li>
												<li><a href="about-us.html">About Us</a></li>
												<li><a href="contact.html">Contact</a></li>
											</ul>
										</nav>

								</div>
							</header>

						<!-- Banner -->
							<div id="banner">
							
							
							<div id="mainContent">
								<div id="chatbox">
								</div>
								<form id="chatForm">
								<label for="content">Message:</label>
								<input type="text" id="content" name="content" class="chatinput">
								<input type="submit" value="Send it!"/>
								</form>
							</div>
							
							<!--
								<form>

								<h2><strong>Computer:</strong> I am listening...<br /><br />
								<input type="text" name="computer"><br>

								<strong>User:</strong> I am interested in...<br /><br />
								<input type="text" name="user">
									</h2>							
									<a href="#" class="button big icon fa-check-circle">Send</a>							
								
								




								   <input type="submit" value="Submit"> 

								</form> 
							-->								
								

							</div>

					</div>
				</div>

			<!-- Main Wrapper -->
				<div id="main-wrapper">
					<div class="wrapper style1">
						<div class="inner">

							<!-- Feature 1 -->
								<section class="container box feature1">

										<div class="12u">
											<header class="first major">
												<h2>Resistance if futile</h2>
												<p>You will be  <strong>assimilated</strong> ...</p>
											</header>
										</div>


								</section>

						</div>
					</div>
					<div class="wrapper style2">
						<div class="inner">



							</div>
					</div>

				</div>

			<!-- Footer Wrapper -->
				<div id="footer-wrapper">
					<footer id="footer" class="container">
						<div class="row">
							<div class="3u 12u(mobile)">

								<!-- Links -->
									
									</section>

							</div>

							<div class="6u 12u(mobile)">

								<!-- Contact -->
									<section>
										<h2>Get in touch</h2>
										<div>
											<div class="row">
												<div class="6u 12u(mobile)">
													<dl class="contact">
														<dt>Twitter</dt>
														<dd><a href="#">@smart-citizen</a></dd>
														<dt>Facebook</dt>
														<dd><a href="#">facebook.com/smart-citizen</a></dd>
														<dt>WWW</dt>
														<dd><a href="#">www.smart-citizen.com</a></dd>
														<dt>Email</dt>
														<dd><a href="#">contact@smart-citizen.com</a></dd>
													</dl>
												</div>
												<div class="6u 12u(mobile)">
													<dl class="contact">
														<dt>Address</dt>
														<dd>
															Avenija Dubrovnik 15<br />
															10020 Zagreb<br />
															Croatia
														</dd>
														<dt>Phone</dt>
														<dd>(000) 000-0000</dd>
													</dl>
												</div>
											</div>
										</div>
									</section>

							</div>
						</div>
						
					</footer>
				</div>

		</div>

		<!-- Scripts -->

			<script src="js/jquery.min.js"></script>
			<script src="js/jquery.dropotron.min.js"></script>
			<script src="js/skel.min.js"></script>
			<script src="js/skel-viewport.min.js"></script>
			<script src="js/util.js"></script>
			<!--[if lte IE 8]><script src="js/ie/respond.min.js"></script><![endif]-->
			<script src="js/main.js"></script>

	</body>
</html>