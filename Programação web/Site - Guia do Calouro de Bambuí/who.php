<?php
    require_once 'conexao.php';
	$email1 = "";
	$descricao1 = "";
	
	if($_SERVER["REQUEST_METHOD"]=="POST"){
		$email1 = $_POST["email1"];
        $descricao1 = $_POST["descricao1"];
		
		$sql = "INSERT INTO contato (email1,descricao1) VALUES (?,?)";
		if($stmt = $conexao->prepare($sql)){
			$stmt->bind_param("ss", $email1, $descricao1);
			
			if($stmt->execute()){
				header("location: who.php");
				exit();			
			} else {
				echo "Acess ERROR";
			}
		}
		$stmt->close();
		$conexao->close();
	}
?>

<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
    <title>Quem somos nós?</title>
      <meta name="viewport" content="width=device-width,initial-scale=1">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
        <!-- Arquivo css, com os estilos -->
        <link rel="stylesheet" type="text/css" href="css/estilos.css">
        <!-- Arquivo javascript -->
        <script src="java.js"></script>
</head>
<body style="background-color: white";>
  <nav class="navbar navbar-expand-md navbar-light" style="background-color: #2E8B57; color:white;">
            <a class="navbar-brand"; style="font-family: Segoe UI Black;">Guia Calouro Bambuí</a>
            <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSite" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
                <span class="navbar-toggler-icon"></span>
            </button>
            <div class="collapse navbar-collapse" id="navbarSite">
                <ul class="navbar-nav mr-auto" >
                  <li class="nav-item active">
                    <a class="nav-link" href="index.php" style="color:white;">Ínicio</a>
                  </li>
                  <li class="nav-item">
                    <a class="nav-link" href="horarios.html" style="color:white;">Horários de Ônibus</a>
                  </li>
                  <!--menu dropdown -->
                  <ul class="navbar-nav">
                     <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" href="#" style="color:white;" data-toggle="dropdown" id="navDrop">Dicas</a>
                            <div class="dropdown-menu">
                                <a class="dropdown-item" href="dormir.html">Onde Dormir?</a>
                                <a class="dropdown-item" href="comer.html">Onde Comer?</a>
                                <a class="dropdown-item" href="lojas.html">Lojas/Comercio</a>
                            </div>
                     </li>
                  </ul>
                  <li class="nav-item">
                    <a class="nav-link" href="who.php"  style="color:white;">Quem somos?</a></li>
                </ul>
              </div>
        </nav>
        <!--titulo da página -->
        <div class="jumbotron text-center"; style="background-color: #3CB371">
              <h1 style="font-family: Segoe UI Black; font-size: 40px; color: white">QUEM SOMOS?</h1>
              <p style="font-family: Segoe UI Black; font-size: 20px; color: white">Objetivo do site</p>
        </div>
    
        <h2 style="text-align: center; font-family: Berlin Sans FB;">Desenvolvedores</h2><br>
        <p style="text-align: center;">Site desenvolvido por Marco Aurélio e Pâmela, discentes em Engenharia de Computação no Instituto Federal de Minas Gerais, para a disciplina de Programação Web, <br> ministrada pelo Professor Eduardo Melo. O objetivo do site é trazer ao aluno ingressante, uma plataforma onde ele tenha acesso as principais informações sobre a<br> cidade de Bambuí - MG e os principais locais que todo universitário frequenta, juntamente com os horários de ônibus para ir ao Instituto.<br> Além disso, o Guia do Calouro também conta com uma aba de anúncios de vagas em repúblicas, para facilitar a vida do estudante que quer anunciar ou esteja a procura de uma vaga.   </p>
        <hr>
        <br>
    
        <!-- descrição dos desenvolvedores-->
        <div class="container" align="center">
            <!-- Marco -->
            <div class="row my-3">
                <div class="col-sm-2">
                    <!-- ESPAÇAMENTO lateral -->
                </div>
                <div class="col-sm-4">
                    <img src="img/marco.jpg"  class="img-responsive" style="border-radius: 50%;" alt="Cinque Terre" width="180">
                </div>
                <div class="col-sm-4">
                    <br>
                    <h4>Marco Aurélio Monteiro Lima</h4><br>
                    <img src="img/instagram.png" class="img-responsive" alt="Cinque Terre" width="28">
                    <a target="_blanck" href="https://www.instagram.com/marcomllima/">@marcomllima</a>
                    <br>
                    <b>E-mail:</b> marco.monteirolima@gmail.com
                </div>
                <div class="col-sm-2">
                    <!-- ESPAÇAMENTO -->
                </div>
            </div>
            <br>
            <br>
            <br>
            <!--Pâmela -->
            <div class="row my-3">
                <div class="col-sm-2">
                    <!-- ESPAÇAMENTO -->
                </div>
                <div class="col-sm-4">
                    <img src="img/pam.jpg" class="img-responsive" style="border-radius: 50%;" alt="Cinque Terre" width="180">
                </div>
                <div class="col-sm-4">
                    <br>
                    <h4>Pâmela Evelyn Carvalho</h4><br>
                    <img src="img/instagram.png" class="img-responsive" alt="Cinque Terre" width="28">
                    <a target="_blanck" href="https://www.instagram.com/pamelaevelync/">@pamelaevelync</a>
                        <br>
                    <b>E-mail:</b> pamelaecarvalho@gmail.com    
                </div>
                <div class="col-sm-2">
                    <!-- ESPAÇAMENTO -->
                </div>
            </div>
            <br><br>
        </div>
        <hr>
    
        <!-- Dicas e Sugestoes-->
            <div class="container">
            <div class="row my-3">
                <div class="col-sm-3">
                    <!-- ESPAÇAMENTO -->
                </div>
                <div class="col-sm-6">
                    <h3 style="text-align: center;">Dicas e sugestões:</h3><br>
                    <!--FORMULARIO De Contato -->
                        <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
                            <table class="table table-borderless">
                                <tr>
                                      <td style="text-align: right"><label for="email1">Email: </label></td>
                                      <td><input type="email" class="form-control" id="email1" name="email1" required>
                                </tr>
                                <tr>
                                       <td style="text-align: right"><label for="descricao1">Sugestão:</label></td>
                                       <td><textarea name="descricao1" class="form-control" rows="4" cols="8" id="descricao1" style="resize:nome;" required></textarea></td>
                                </tr>
                                <tr>
                                    <td colspan="2">
                                        <button type="submit" onclick="sugestaoEnviada()" name="enviar" id="enviar" class="btn btn-success btn-block">Enviar</button>
                                    </td>
                                </tr>
                            </table>
                        </form>
                </div>
                <div class="col-sm-3">
                    <!-- ESPAÇAMENTO -->
                </div>
            </div>         
        </div>
    
    <!--rodapé -->
        <div class="jumbotron jumbotron-fluid">
            <div class="container">
                <div class="row">
                    <div class="col-12 text-center">
                            <h1 class="display-5"><i class="fa fa-video-camera text-primary" aria-hidden="true"></i>Guia Calouro Bambuí</h1>
                            <p class="lead">Site feito de aluno para aluno<br>Aproveite o site e nos siga no instagram.</p>
                            <img src="img/instagram.png" class="img-responsive" alt="Cinque Terre" width="20"><a target="_blanck" href="https://www.instagram.com/marcomllima/"> @marcomllima</a>,
                            <img src="img/instagram.png" class="img-responsive" alt="Cinque Terre" width="20"><a target="_blanck" href="https://www.instagram.com/pamelaevelync/"> @pamelaevelync</a>
                            <hr>
                            <!-- Footer -->
                            <footer class="page-footer font-small stylish-color-dark pt-4 mt-4">
                              <!-- Footer Links -->
                              <!-- Copyright -->
                              <div class="footer-copyright text-center py-1">© 2018 Copyright:
                                <a href="who.php"> Marco Aurélio e Pâmela </a>
                              </div>
                              <!-- Copyright -->
                            </footer>
                            <!-- Footer -->
                    </div>
                </div>                
            </div>          
        </div>
    
</body>
</html>