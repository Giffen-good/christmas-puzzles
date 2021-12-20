<?php
define("FILENAME", "day-4-input.txt");
$file = fopen(FILENAME,"r");
$i = 0;
$game;
$card;



while ($line = fgets($file)) 
{
    $i++;
    if ($i == 1) 
    {
        $game = initGame($line);
        continue;
    }

    if ($line == "\n")
    {
        if (isset($card))
        {
            $game->addBingoCard($card);
        }
        $card = new BingoCard;

    } else {
        
        $fmt = rtrim(preg_replace('!\s+!', ' ', $line));
        $row = explode(" ", $fmt);
        $card->addRow($row);

    }

}
fclose($file);

// Let's Go!
$game->play();





function initGame($line): BingoCompetition {
    $draw = explode(',', $line);
    return new BingoCompetition($draw);
}

class BingoCard 
{

    public $card = [];

    public function addRow(array $row)
    {
        array_push($this->card, $row);
    }
    
    public function checkRows(array $draw)
    {
        foreach ($this->card as $row)
        {
            if ($this->checkLine($row, $draw)) return true;
        }
        return false;
    }

    public function checkLine(array $line, array $draw)
    {
        $line_has_bingo = true;
        $d = implode(' ', $draw);
        $l = implode(' ', $line);
        
        foreach ($line as $val)
        {
            if (!in_array($val, $draw)) $line_has_bingo = false;
        }
        return $line_has_bingo;
    }

    public function checkColumns(array $draw)
    {
        for ( $i = 0; $i < count($this->card); $i++)
        {
            $col = [];
            foreach ($this->card as $row)
            {
                array_push($col, $row[$i]);
            }
            if ($this->checkLine($col, $draw)) return true;
        }
        return false;
    }

    public function checkForBingo(array $draw)
    {
        
        return $this->checkRows($draw) || $this->checkColumns($draw);
    }
}


class BingoCompetition
{
    private $draw;
    public $winner;
    public $numbers_drawn = [];
    public array $competetitors;

    private function drawNextValue(): void
    {
        array_push($this->numbers_drawn, array_shift($this->draw));
        xdebug_break();
    }

    private function checkForWinners(): array // of Bingo Cards
    {
        $winners = [];
        foreach ($this->competetitors as $card)
        {
            $isWinner = $card->checkForBingo($this->numbers_drawn);
            if ($isWinner) array_push($winners, $isWinner);
        }
        return $winners;
    }

    function __construct(array $draw)
    {
        $this->draw = $draw;
    }

    public function addBingoCard(BingoCard $card): void
    {
        $this->competetitors[] = $card;
    }

    public function play(): void
    {
        $i = 0;
        while (!$this->winner && $this->draw)
        {
            $this->drawNextValue();
            $this->winner = $this->checkForWinners();
            $i++;
        }
        
    }
}

