<?php 
use yii\helpers\Html;
use yii\helpers\Url;
use yii\bootstrap4\Modal;
?>

<div class="row">
	<div class="col-xs-12">
		<div class="card">
			<div class="card-header">
				<h3 class="card-title"><i class="fas fa-shopping-cart"></i> <?=Yii::t('app', 'My cart')?> </h3>
			</div>
			<div class="card-body table-responsive no-padding">
				<table class="table table-hover">
					<thead>
						<tr class="active">
							<th> <?=Yii::t('app', 'Image')?></th>
							<th> <?=Yii::t('app', 'Description')?></th>
							<th> <?=Yii::t('app', 'Quantity')?></th>
							<th> <span class="label label-success">
									<i class="fas fa-plus"> </i>
								  </span>
								</th>
							<th> <span class="label label-success">
									<i class="fas fa-minus"> </i>
								  </span> 
								</th>
							<th> <?=Yii::t('app', 'Price')?></th>
							<th> <?=Yii::t('app', 'Subtotal')?></th>
							<th> <i aria-hidden="true">&times;</i></th>
						</tr>					
					</thead>
					<tbody>	
					<?php foreach($cartItems as $item) {?>
						<tr>
							<td>  
							<?=yii\helpers\Html::img(\Yii::$app->request->BaseUrl.'/'
                            .Yii::$app->params['uploadImage'].$item->getProduct()->image,['height'=>50])
                     ?>
                     	</td>
                     <td>
								<?=Html::a($item->getProduct()->name, ['view', 'code' => $item->getProduct() -> code],
									['id' => 'popipModalCart'. $item->getProduct()->code]							
								)?>
								</td>
							<td> 
								<?=$item->getQuantity()?>
								</td>
							<td>
								<a href="<?=Url::to(['store/add','code'=> $item->getProduct()->code])?>" 
									title="<?=Yii::t('app','Add {0}', $item->getProduct()->name)?>">
									<i class="fas fa-plus"></i>
								</a>
								</td>
							<td>
								<a href="<?=Url::to(['store/substract','code'=> $item->getProduct()->code])?>" 
									title="<?=Yii::t('app','Substract {0}', $item->getProduct()->name)?>">
									<i class="fas fa-minus"></i>
								</a> 
								</td>
							<td>
								<?=$item->getPrice()?> 
								</td>
							<td>
								<?=number_format($item->getCost(),2)?>
								</td>
							<td>
								<a href="<?=Url::to(['store/remove','code'=> $item->getProduct()->code])?>" 
									title="<?=Yii::t('app','Delete {0}', $item->getProduct()->name)?>">
									<i class="fas fa-trash"></i>
								</a>
								</td>						
						</tr>										
					<?php } ?>
							<tr class="active">
								<td colspan="1"><?=Yii::t('app','Total qty')?>:</td>
								<td colspan="7"><?=$cart->getTotalCount()?></td>
								</tr>
							<tr class="active">
								<td colspan="1"><?=Yii::t('app','Total')?>:</td>
								<td colspan="7"><?=number_format($cart->getTotalCost(),2)?></td>
								</tr>
					</tbody>			
				</table>
			</div>
			<div class="box-footer">
				<?=Html::a(Yii::t('app','Remove cart'), ['/store/delete'],[
					'class' => 'btn btn-default',
					'data' => ['confirm' => Yii::t('app','Are you sure you want to delete this item?'),
									'method' => 'post'					
								 ],
				])?>
				<a href="<?=Url::to(['/guets/create'])?>" 
							class = 'btn btn-primary float-right'>
							<?=Yii::t('app','Order')?>
				</a>
			</div>
		</div>
	</div>
</div>
<?php
Modal::begin([
	'id' => 'modalCart',
	'size' => 'modal-lg',
	'title' => '<b>' .Yii::t('app','Product').'</b>',
	]);
Modal::end();

foreach($cartItems as $item){
	$this->registerJs("$(function() {
		$('#popupModalCart".$item->getProduct()->code."').click(function(e){
			e.preventDefault();
			$('#modalCart').modal('show').find('.modal-body').load($(this).attr('href'));		
		});
	});");
}
?>





