unit untPropertyHints;

interface

function GetPropertyHint(const PropertyId: String): String;

implementation

type
  TPropertyHint = record
  public
    PropertyId: String;
    PropertyHint: String;
  end;

const
  PropertyHints: array[0..7] of TPropertyHint =
  (
    (
      PropertyId  : 'Filter.FilterType';
      PropertyHint: 'The filter type.'
    ),
    (
      PropertyId  : 'Filter.FilterFlags';
      PropertyHint: 'The filter flags.'
    ),
    (
      PropertyId  : 'Filter.FilterFlags.iffIsRootTable';
      PropertyHint: 'This is the root table.'
    ),
    (
      PropertyId  : 'Filter.FilterFlags.iffIsStaticFilter';
      PropertyHint: 'This is a static filter that should not be removed.'
    ),
    (
      PropertyId  : 'Filter.FilterFlags.iffIsDefinitionContainer';
      PropertyHint: 'This is a definition container and not an actual filter.'
    ),
    (
      PropertyId  : 'Filter.NeutralElementType';
      PropertyHint: 'The neutral element type of the filter. Possible values:' + #13#10#13#10 +
                    '- netNotAvailable' + #13#10 +
                    'The neutral "zero" element is not supported.' + #13#10 +
                    '- netPlaceholder' + #13#10 +
                    'The neutral "zero" element is supported and used as a placeholder. ' +
                    'The filter will signal a conflict, if the neutral element AND at least one ' +
                    'regular value is set.' + #13#10 +
                    '- netValue' + #13#10 +
                    'The neutral "zero" element is supported and can be used as a regular value.'
    ),
    (
      PropertyId  : 'Filter.Capacity';
      PropertyHint: 'The maximum capacity of the filter.'
    ),
    (
      PropertyId  : 'Filter.ItemCount';
      PropertyHint: 'The actual number of non-empty slots in the filter.'
    )
  );

function GetPropertyHint(const PropertyId: String): String;
var
  I: Integer;
begin
  Result := 'No info text available.';
  for I := Low(PropertyHints) to High(PropertyHints) do
  begin
    if (PropertyHints[I].PropertyId = PropertyId) then
    begin
      Exit(PropertyHints[I].PropertyHint);
    end;
  end;
end;

end.
