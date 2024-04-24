/**
 * @overview Javascript functions and constants for lab-5-javascript
 * 
 * @todo For each of the JSDOC comments below, create a function with with the 
 * described functionality. These docstrings should help inform you what the 
 * function should be named, what parameters it takes, and where the function 
 * is used (i.e. the html page to open for validating your code).
 * 
 * For more detailed instructions, please refer to the lab doc.
 * @link https://cuboulder-csci-3308.herokuapp.com/Labs/lab5_javascript
 */

/**
 * @global players
 * 
 * Players is an array to hold each player's information.
 *
 * Fields:
 *  @prop {string} name Football player's name
 *  @prop {string} img The relative/absolute path to the image file.
 *  @prop {string} alt The alternative text that describes the image.
 *  @prop {string} year The student's year in college (Freshman, Sophomore, 
 *   Junior, Senior).
 *  @prop {string} major The student's current college major.
 *  @prop {number} games_played The number of football games the student has 
 *   played for the Buffs.
 *  @prop {number} pass_yards - The total number of passing yards in the 
 *    student's football career for the Buffs.
 *  @prop {number} rushing_yards - The total number of rushing yards in the 
 *    student's football career for the Buffs.
 *  @prop {number} receiving_yards - The total number of receiving yards in the 
 *    student's football career for the Buffs.
 */
const players = [
  {
    name: "John Doe",
    img: "../resources/img/player1.jpg",
    alt: "Image of Player 1",
    year: "Sophomore",
    major: "Art",
    games_played: 23,
    pass_yards: 435,
    rushing_yards: 200,
    receiving_yards: 88,
  },
  {
    name: "James Smith",
    img: "../resources/img/player2.jpg",
    alt: "Image of Player 2",
    year: "Junior",
    major: "Science",
    games_played: 17,
    pass_yards: 192,
    rushing_yards: 102,
    receiving_yards: 344,
  },
  {
    name: "Samuel Phillips",
    img: "../resources/img/player3.jpg",
    alt: "Image of Player 3",
    year: "Freshman",
    major: "Math",
    games_played: 8,
    pass_yards: 35,
    rushing_yards: 70,
    receiving_yards: 98,
  },
  {
    name: "Robert Myers",
    img: "../resources/img/player4.jpg",
    alt: "Image of Player 4",
    year: "Senior",
    major: "Computer Science",
    games_played: 31,
    pass_yards: 802,
    rushing_yards: 375,
    receiving_yards: 128,
  },
];

/**
 * @func viewStudentStats
 * @page register.html
 *
 * @todo This method will accept the id of an html tag and a toggle value.
 * The method will then set the html tag's css visibility and height.
 * To hide the html tag (toggle - 0), the visibility will be set to hidden and
 * the height will be set to 0. To reveal the html tag (toggle - 1), the
 * visibility will be set to visible and the height will be set to auto.
 *
 *
 * @param {string} id The css id of the html tag being updated.
 * @param {...number} toggle A number 0/1 predicate indicating the toggle
 *  0 -> Hide the HTML tag visible
 *  1 -> Make the HTML tag visible
 */

 function viewStudentStats(id, toggle) {
  
  if (toggle == 0) {
      document.getElementById(id).style.visibility = "hidden";
      document.getElementById(id).style.height = "0";
  } else {
      document.getElementById(id).style.visibility = "visible";
      document.getElementById(id).style.height = "auto";
  }

}


/**
 * @func changeColor
 * @page home.html
 * 
 * @todo This method will set the html body's background color to the color 
 * specified.
 *
 * @param {string} color A css color
 */

function changeColor(color) {

    document.body.style.background = color;


}


/**
 * @func loadStatsPage
 * @page team_stats.html
 * 
 * @todo This method will iterate through the stats t1 and do the following:
 * 1. Read through each row of the t1 & determine which team won the game.
 * 2. Update the winner column to the name of the winning team.
 * 3. Keep track of the number of wins/losses for the Buffs.
 * 4. Update the second t1 to show the total number of wins/losses for the 
 *    Buffs.
 */
 
 
function loadStatsPage() {
  
  var wins = 0;
  var losses = 0;   
  
  var table = document.getElementById("stats_table");

    

  for (var i = 2; i < table.rows.length; i++) {

        var homeS = parseInt(table.rows[i].cells[2].innerHTML);
        var oppS = parseInt(table.rows[i].cells[3].innerHTML);

        var winner;

        if (homeS > oppS) {

            winner = "CU";
            wins++;

        } else if (oppS > homeS) {

            winner = table.rows[i].cells[1].innerHTML;
            losses++;
        
          } else {

            winner = "Tie";

          }

          table.rows[i].cells[4].innerHTML = winner;

  }

      document.getElementById('wins').innerHTML = wins;
      document.getElementById('losses').innerHTML = losses;

}
    

     

/** 
 * @func loadPlayersPage 
 * @page player_info.html
 * 
 * @todo This method will populate the dropdown menu to allow the user to 
 * select which player's information to view. 
 * 
 * To handle this, you will need to iterate through the players array and do 
 * the following for each player:
 * 1. Create an anchor tag
 * 2. Set the href to "#", this will make sure the anchor tag doesn't change 
 *    pages
 * 3. Set the onclick to call switchPlayers method (this will need to pass in 
 *    the index inside the players array)
 * 4. Set the anchor tag's text to the player's name. 
 * 
 * After setting all of the anchor tags, update the innerHTML of the dropdown 
 * menu. As a hint, the id for the dropdown menu is `player_selector`.
 */

function loadPlayersPage() {

    var display;

    for (var i = 0; i < players.length; i++) {

        display += '<a class="dropdown-item" href="#" onclick = "switchPlayers(' + i + ')">' + players[i].name + '</a>';

    }

    return document.getElementById("player_selector").innerHTML = display;


}



/**
 * @func switchPlayers
 * @file player_info.html
 * 
 * This method will update the the spans on the player's information page
 * and calculate the average passing, rushing, and receiving yards.
 * 
 * Span ids:
 *   p_year        - The player's year in college
 *   p_major       - The player's major in college
 *   g_played      - The number of games played for Buffs
 *   player_img    - The player's photo (must set src and alt)
 *   p_yards       - The number of passing yards
 *   r_yards       - The number of rushing yards
 *   rec_yards     - The number of receiving yards
 * 
 * Calculated values:
 *   avg_p_yards   - The average number of passing yards for the player's Buff 
 *                   career per game
 *   avg_r_yards   - The average number of rushing yards for the player's Buff 
 *                   career per game
 *   avg_rec_yards - The average number of receiving yards for the player's 
 *                   Buff career per game.
 * 
 * 
 @param {number} playerNum The index of the football player in the players 
 *   array.
 */

 function switchPlayers(playerN)
{
	document.getElementById("p_year").innerHTML = players[playerN].year;

	document.getElementById("p_major").innerHTML = players[playerN].major;
	
  document.getElementById("g_played").innerHTML = players[playerN].games_played;
	
  document.getElementById("player_img").innerHTML = players[playerN].img;
	
  document.getElementById("p_yards").innerHTML = players[playerN].pass_yards;
	
  document.getElementById("r_yards").innerHTML = players[playerN].rushing_yards;
	
  document.getElementById("rec_yards").innerHTML = players[playerN].receiving_yards;
	
  document.getElementById("avg_p_yards").innerHTML = (players[playerN].pass_yards)/(players[playerN].games_played);
	
  document.getElementById("avg_r_yards").innerHTML = (players[playerN].rushing_yards)/(players[playerN].games_played);
	
  document.getElementById("avg_rec_yards").innerHTML = (players[playerN].receiving_yards)/(players[playerN].games_played);

}

