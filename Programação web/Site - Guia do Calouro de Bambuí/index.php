<!--metodo de inserção -->
<?php	
	if(isset($_FILES["imgpost"]) && isset($_POST["titulo"]) && isset($_POST["endereco"]) && isset($_POST["telefone"]) && isset($_POST["email"])) {
        require_once 'conexao.php';    
        $imgpost =$_FILES["imgpost"];
        
        $titulo = $_POST["titulo"];
		$endereco = $_POST["endereco"];
		$telefone = $_POST["telefone"];
        $email = $_POST["email"];
    
        $destino = "arquivos/";
        $arqnome = $imgpost['name'];
    	//echo "Passei e peguei os valores";
        move_uploaded_file($imgpost['tmp_name'], $destino . $arqnome);
        
		$sql = "INSERT INTO publicacao (titulo,endereco,telefone, email, imgpost, destino) VALUES (?,?,?,?,?,?)";
        //echo "sql:".$sql;
		if($stmt = $conexao->prepare($sql)){
          //  echo "passei";
			$stmt->bind_param("ssssss", $titulo, $endereco, $telefone, $email, $arqnome, $destino);
			
			if($stmt->execute()){
			     header("location: index.php");
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
<html lang="pt-br">
    <head>
		<meta charset="utf-8">
		<title>Ínicio</title>
	    <meta name="viewport" content="width=device-width,initial-scale=1">
        <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
        <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
        <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
        <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>  
        <script type="https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
        <!-- Arquivo css, com os estilos -->
        <link rel="stylesheet" type="text/css" href="css/estilos.css">
	</head>
	<body>
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
        <!--carrousel -->
        <div class="container-fluid">
        <div id="carouselSite" class="carousel slide" data-ride="carousel">
            <ol class="carousel-indicators">
              <li data-target="#carouselSite" data-slide-to="0" class="active"></li>
              <li data-target="#carouselSite" data-slide-to="1"></li>
              <li data-target="#carouselSite" data-slide-to="2"></li>
            </ol>
            <div class="carousel-inner">
                <div class="carousel-item active">
                    <img src="img/slide11.jpg" class="img-fluid d-block">
                </div>
                <div class="carousel-item">
                    <img src="img/slide2.jpg" class="img-fluid d-block">
                </div>
                <div class="carousel-item">
                    <img src="img/slide3.png" class="img-fluid d-block">
                </div>
            </div>
            <a class="carousel-control-prev" href="#carouselSite" role="button" data-slide="prev">
                <span class="carousel-control-prev-icon"></span>
                <span class="sr-only">Anterior</span>
            </a>
            <a class="carousel-control-next" href="#carouselSite" role="button" data-slide="next">
                <span class="carousel-control-next-icon"></span>
                <span class="sr-only">Avançar</span>
                    </a>
        </div></div>
        <br>

        <!--contéudo da página-->
        <div class="container">
            <h2 style="text-align: center; font-family: Berlin Sans FB;">Anuncie vagas em repúblicas de Bambuí</h2>
            <br>
            <div class="row" align="center">
                <button data-toggle="modal" data-target="#siteModal" type="button" style="background: #FF8C00"; class="btn btn-success btn-lg btn-block ">Anunciar vaga
                </button>
            </div>
            <hr>
            <h2 style="text-align: center;">Últimas postagens:</h2>
            <hr>
            <div class="row">
                <!-- organizar as publicações em cards -->
                <?php
                    require_once 'conexao.php';
                      $sql = "SELECT * FROM publicacao";
                      if ($resultado = $conexao->query($sql)){
                        if($resultado->num_rows > 0){
                          echo "<div class='container'>";
                           echo "<div class='row'>";
                            echo "<div class='row justify-content-sm-center'>";
                            while($linha = $resultado->fetch_array()){
                              echo "<div class='col-lg-4 col-md-4'>";
                               echo "<div class='card border-secondary mb-3 mb-5'>";
                                echo "<img class='card-img-top' src=".$linha['destino'].$linha['imgpost']." >";
                                echo "<div class='card-body'>";                                    
                                 echo "<hr>";
                                 echo "<h4 class='card-title' style='text-align: center;'>" . $linha['titulo'] . "</h4>";
                                 echo "<hr>";
                                 echo "<h5>Endereço:</h5>";
                                 echo "<p class='card-text'>" . $linha['endereco'] . "</p>";
                                 echo "<h5>Telefone:</h5>";
                                 echo "<p class='card-text'>" . $linha['telefone'] . "</p>";
                                 echo "<h5>Email:</h5>";
                                 echo "<p class='card-text'>" . $linha['email'] . "</p>";                                              
                                echo "</div>";
                               echo "</div>";
                              echo "</div>";
                            }
                            echo "</div>";
                           echo "</div>";
                          echo "</div>";
                         $resultado->free();
                        }else{
                            echo "<p class='lead'>Nenhum registro encontrado.</p>";
                        }
                        }else{
                            echo "Erro ao executar o comando executado SQL.";
                        }
                        $conexao->close();
                ?>
                <hr>
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

        <!-- Modal -->
        <!-- formulario da janela de publicação -->
        <div class="modal fade" id="siteModal" tabindex="-1" role="dialog">
            <div class="modal-dialog modal-lg" role="document">
                <!--FORMULARIO DO CADASTRO -->
                <form method="post" enctype="multipart/form-data" action="">
                        <div class="modal-content">
                            <div class="modal-header">
                                <h5 class="modal-title">Preencha os dados abaixo:</h5>
                                <button type="button" class="close" data-dismiss="modal">
                                    <span>&times;</span>
                                </button>
                            </div>
                            <div class="modal-body">
                                <div class="container-fluid">
                                        <div class="col-12">
                                            <table class="table">
                                                <tr>
                                                    <td style="text-align: right"><label for="titulo">Titulo:</label></td>
                                                    <td><input type="text" class="form-control" id="titulo" name="titulo" placeholder="Titulo da publicação seja breve." required></td>
                                                </tr>
                                                <tr>
                                                    <td style="text-align: right"><label for="endereco">Endereço:</label></td>
                                                    <td><input type="text" class="form-control" id="endereco" name="endereco" placeholder="Endereço" required></td>
                                                </tr>
                                                <tr>
                                                    <td style="text-align: right"><label for="telefone">Telefone:</label></td>
                                                    <td><input type="text" class="form-control" id="telefone" name="telefone" pattern="\(\d{2}\)\d{4}-\d{4}" placeholder="Ex: (00)0000-0000" required></td>
                                                </tr>
                                                <tr>
                                                    <td style="text-align: right"><label for="email">Email: </label></td>
                                                    <td><input type="email" class="form-control" id="email" name="email" placeholder="email" required>
                                                </tr>
                                                <tr>
                                                    <td colspan="2" >
                                                        <div class="custom-file">
							                                 <input type="file" class="custom-file-input" id="imgpost" name="imgpost" required>
							                                 <label class="custom-file-label" for="imgpost">Inserir Imagem</label>
							                                 <div class="invalid-feedback">Example invalid custom file feedback</div>
                                                        </div>
                                                    </td>
                                                
                                                </tr>
                                            </table>                                            
                                        </div>
                                </div> 
                            </div>
                            <div class="modal-footer">
                                <button type="submit" name="publicar" id="publicar" class="btn btn-success btn-block">Publicar</button>
                            </div>                        
                        </div>
                </form>
            </div>
        </div>
	</body>
</html>